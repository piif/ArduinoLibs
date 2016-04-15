/**
 * copyright Christian Lefebvre 2016, released under LGPL
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
//#include "Arduino.h"

#include "simpleSerial.h"
#include "../vprintf/vprintf.h"

#if !(defined(UBRRH) || defined(UBRR0H))
	#warning "No hardware serial found"

	void serialBegin(unsigned long, uint8_t) {}
	void serialEnd() {}
	int serialAvailable(void) {}
	int serialPeek(void) {}
	int serialRead(void) {}
	int serialAvailableForWrite(void) {}
	void serialFlush(void) {}
	size_t serialWrite(uint8_t) {}
#else
	#if defined(UBRRH) && defined(UBRRL)
		#define _ubrrh UBRRH
		#define _ubrrl UBRRL
		#define _ucsra UCSRA
		#define _ucsrb UCSRB
		#define _ucsrc UCSRC
		#define _udr   UDR
	#else
		#define _ubrrh UBRR0H
		#define _ubrrl UBRR0L
		#define _ucsra UCSR0A
		#define _ucsrb UCSR0B
		#define _ucsrc UCSR0C
		#define _udr   UDR0
	#endif


// Ensure that the various bit positions we use are available with a 0
// postfix, so we can always use the values for UART0 for all UARTs. The
// alternative, passing the various values for each UART to the
// HardwareSerial constructor also works, but makes the code bigger and
// slower.
#if !defined(TXC0)
	#if defined(TXC)
		// Some chips like ATmega8 don't have UPE, only PE. The other bits are
		// named as expected.
		#if !defined(UPE) && defined(PE)
			#define UPE PE
		#endif
		// On ATmega8, the uart and its bits are not numbered, so there is no TXC0 etc.
		#define TXC0 TXC
		#define RXEN0 RXEN
		#define TXEN0 TXEN
		#define RXCIE0 RXCIE
		#define UDRIE0 UDRIE
		#define U2X0 U2X
		#define UPE0 UPE
		#define UDRE0 UDRE
	#elif defined(TXC1)
		// Some devices have uart1 but no uart0
		#define TXC0 TXC1
		#define RXEN0 RXEN1
		#define TXEN0 TXEN1
		#define RXCIE0 RXCIE1
		#define UDRIE0 UDRIE1
		#define U2X0 U2X1
		#define UPE0 UPE1
		#define UDRE0 UDRE1
	#else
		#error No UART found in HardwareSerial.cpp
	#endif
#endif // !defined TXC0

// Has any byte been written to the UART since begin()
uint8_t _written;

volatile rx_buffer_index_t _rx_buffer_head;
volatile rx_buffer_index_t _rx_buffer_tail;
volatile tx_buffer_index_t _tx_buffer_head;
volatile tx_buffer_index_t _tx_buffer_tail;

// Don't put any members after these buffers, since only the first
// 32 bytes of this struct can be accessed quickly using the ldd
// instruction.
unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void _tx_udr_empty_irq(void)
{
  // If interrupts are enabled, there must be more data in the output
  // buffer. Send the next byte
  unsigned char c = _tx_buffer[_tx_buffer_tail];
  _tx_buffer_tail = (_tx_buffer_tail + 1) % SERIAL_TX_BUFFER_SIZE;

  _udr = c;

  // clear the TXC bit -- "can be cleared by writing a one to its bit
  // location". This makes sure flush() won't return until the bytes
  // actually got written
  sbi(_ucsra, TXC0);

  if (_tx_buffer_head == _tx_buffer_tail) {
    // Buffer empty, so disable interrupts
    cbi(_ucsrb, UDRIE0);
  }
}

// Public Methods //////////////////////////////////////////////////////////////

void serialBegin(unsigned long baud, uint8_t config)
{
  // Try u2x mode first
  uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
  _ucsra = 1 << U2X0;

  // hardcoded exception for 57600 for compatibility with the bootloader
  // shipped with the Duemilanove and previous boards and the firmware
  // on the 8U2 on the Uno and Mega 2560. Also, The baud_setting cannot
  // be > 4095, so switch back to non-u2x mode if the baud rate is too
  // low.
  if (((F_CPU == 16000000UL) && (baud == 57600)) || (baud_setting >4095))
  {
    _ucsra = 0;
    baud_setting = (F_CPU / 8 / baud - 1) / 2;
  }

  // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
  _ubrrh = baud_setting >> 8;
  _ubrrl = baud_setting;

  _written = 0;

  //set the data bits, parity, and stop bits
#if defined(__AVR_ATmega8__)
  config |= 0x80; // select UCSRC register (shared with UBRRH)
#endif
  _ucsrc = config;

  sbi(_ucsrb, RXEN0);
  sbi(_ucsrb, TXEN0);
  sbi(_ucsrb, RXCIE0);
  cbi(_ucsrb, UDRIE0);
}

void serialEnd()
{
  // wait for transmission of outgoing data
  while (_tx_buffer_head != _tx_buffer_tail)
    ;

  cbi(_ucsrb, RXEN0);
  cbi(_ucsrb, TXEN0);
  cbi(_ucsrb, RXCIE0);
  cbi(_ucsrb, UDRIE0);

  // clear any received data
  _rx_buffer_head = _rx_buffer_tail;
}

int serialAvailable(void)
{
  return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int serialPeek(void)
{
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    return _rx_buffer[_rx_buffer_tail];
  }
}

int serialRead(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    unsigned char c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
    return c;
  }
}

int serialAvailableForWrite(void)
{
#if (SERIAL_TX_BUFFER_SIZE>256)
  uint8_t oldSREG = SREG;
  cli();
#endif
  tx_buffer_index_t head = _tx_buffer_head;
  tx_buffer_index_t tail = _tx_buffer_tail;
#if (SERIAL_TX_BUFFER_SIZE>256)
  SREG = oldSREG;
#endif
  if (head >= tail) return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
  return tail - head - 1;
}

void serialFlush()
{
  // If we have never written a byte, no need to flush. This special
  // case is needed since there is no way to force the TXC (transmit
  // complete) bit to 1 during initialization
  if (!_written)
    return;

  while (bit_is_set(_ucsrb, UDRIE0) || bit_is_clear(_ucsra, TXC0)) {
    if (bit_is_clear(SREG, SREG_I) && bit_is_set(_ucsrb, UDRIE0))
	// Interrupts are globally disabled, but the DR empty
	// interrupt should be enabled, so poll the DR empty flag to
	// prevent deadlock
	if (bit_is_set(_ucsra, UDRE0))
	  _tx_udr_empty_irq();
  }
  // If we get here, nothing is queued anymore (DRIE is disabled) and
  // the hardware finished tranmission (TXC is set).
}

int8_t serialWrite(uint8_t c)
{
  // If the buffer and the data register is empty, just write the byte
  // to the data register and be done. This shortcut helps
  // significantly improve the effective datarate at high (>
  // 500kbit/s) bitrates, where interrupt overhead becomes a slowdown.
  if (_tx_buffer_head == _tx_buffer_tail && bit_is_set(_ucsra, UDRE0)) {
    _udr = c;
    sbi(_ucsra, TXC0);
    return 1;
  }
  tx_buffer_index_t i = (_tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;

  // If the output buffer is full, there's nothing for it other than to
  // wait for the interrupt handler to empty it a bit
  while (i == _tx_buffer_tail) {
    if (bit_is_clear(SREG, SREG_I)) {
      // Interrupts are disabled, so we'll have to poll the data
      // register empty flag ourselves. If it is set, pretend an
      // interrupt has happened and call the handler to free up
      // space for us.
      if(bit_is_set(_ucsra, UDRE0))
	_tx_udr_empty_irq();
    } else {
      // nop, the interrupt handler will free up space for us
    }
  }

  _tx_buffer[_tx_buffer_head] = c;
  _tx_buffer_head = i;

  sbi(_ucsrb, UDRIE0);
  _written = 1;

  return 1;
}

#if defined(USART_RX_vect)
  ISR(USART_RX_vect)
#elif defined(USART0_RX_vect)
  ISR(USART0_RX_vect)
#elif defined(USART_RXC_vect)
  ISR(USART_RXC_vect) // ATmega8
#else
  #error "Don't know what the Data Received vector is called for Serial"
#endif
  {
	if (bit_is_clear(_ucsra, UPE0)) {
	  // No Parity error, read byte and store it in the buffer if there is
	  // room
	  unsigned char c = _udr;
	  rx_buffer_index_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;

	  // if we should be storing the received character into the location
	  // just before the tail (meaning that the head would advance to the
	  // current location of the tail), we're about to overflow the buffer
	  // and so we don't write the character or advance the head.
	  if (i != _rx_buffer_tail) {
		_rx_buffer[_rx_buffer_head] = c;
		_rx_buffer_head = i;
	  }
	} else {
	  // Parity error, read byte but discard it
		unsigned char c = _udr;
	};
  }

#if defined(UART0_UDRE_vect)
ISR(UART0_UDRE_vect)
#elif defined(UART_UDRE_vect)
ISR(UART_UDRE_vect)
#elif defined(USART0_UDRE_vect)
ISR(USART0_UDRE_vect)
#elif defined(USART_UDRE_vect)
ISR(USART_UDRE_vect)
#else
  #error "Don't know what the Data Register Empty vector is called for Serial"
#endif
{
  _tx_udr_empty_irq();
}

#endif // whole file

// This part is outside of global # if to make it available from
// test code examples/testPrintf

int serialPrintf(char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int len = gvprintf(serialWrite, fmt, ap);
	va_end(ap);
	return len;
}
