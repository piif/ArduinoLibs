/**
 * light version of HardwareSerial.h limited to serial0 and without C++
 * Everything is a copy of standard arduino HardwareSerial lib, converted in C syntax
 */

#ifndef simpleSerial_h
#define simpleSerial_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
// NOTE: a "power of 2" buffer size is reccomended to dramatically
//       optimize all the modulo operations for ring buffers.
#if !(defined(SERIAL_TX_BUFFER_SIZE) && defined(SERIAL_RX_BUFFER_SIZE))
#if (RAMEND < 1000)
#define SERIAL_TX_BUFFER_SIZE 16
#define SERIAL_RX_BUFFER_SIZE 16
#else
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64
#endif
#endif
#if (SERIAL_TX_BUFFER_SIZE>256)
typedef uint16_t tx_buffer_index_t;
#else
typedef uint8_t tx_buffer_index_t;
#endif
#if  (SERIAL_RX_BUFFER_SIZE>256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif

// Define config for Serial.begin(baud, config);
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

//    void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
void serialBegin(unsigned long, uint8_t);
void serialEnd();
int serialAvailable(void);
int serialPeek(void);
int serialRead(void);
int serialAvailableForWrite(void);
void serialFlush(void);
int8_t serialWrite(uint8_t);
//    inline size_t write(unsigned long n) { return write((uint8_t)n); }
//    inline size_t write(long n) { return write((uint8_t)n); }
//    inline size_t write(unsigned int n) { return write((uint8_t)n); }
//    inline size_t write(int n) { return write((uint8_t)n); }
//    using Print::write; // pull in write(str) and write(buf, size) from Print

//// Interrupt handlers - Not intended to be called externally
//inline void _rx_complete_irq(void);
//void _tx_udr_empty_irq(void);

int serialPrintf(char *s, ...);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
