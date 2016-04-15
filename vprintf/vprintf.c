/**
 * copyright Christian Lefebvre 2016, released under LGPL
 */

#include "vprintf.h"
#include <inttypes.h>
#include <avr/pgmspace.h>

#define outputChar(c) (*writeChar)(c);len++

int i2h(writeCharFunc writeChar, uint32_t v, uint8_t size) {
	uint8_t delta = size * 8 - 4;
	uint32_t mask = ((uint32_t)0x0F) << delta;
	uint8_t i = size * 2;
	while (i) {
		char c = (v & mask) >> delta;
		(*writeChar)((c < 10) ? (c + '0') : (c - 10 + 'a'));
		v <<= 4;
		i--;
	}
	return size * 2;
}
int i2b(writeCharFunc writeChar, uint32_t v, uint8_t size) {
	uint32_t mask = ((uint32_t)0x01) << (size * 8 - 1);
	while(mask) {
		(*writeChar)((v & mask) ? '1' : '0');
		mask >>= 1;
	}
	return size * 8;
}

int i2u(writeCharFunc writeChar, uint32_t v) {
	int len =  1;
	char mod = v % 10;
	v /= 10;
	if (v != 0) {
		 len += i2u(writeChar, v);
	}
	(*writeChar)(mod + '0');
	return len;
}
int i2d(writeCharFunc writeChar, uint32_t v, uint8_t size, uint8_t withSign) {
	if (v == 0) {
		(*writeChar)('0');
		return 1;
	}

	int len = 0;
	if (withSign) {
		// output sign if < 0, then negate and continue as if unsigned
		if (v & (1 << (size * 8 - 1))) {
			(*writeChar)('-');
			len++;
			v = ~v + 1;
		}
	}
	if (size == 1) {
		v &= 0xFF;
	} else if (size == 2) {
		v &= 0xFFFF;
	}
	return len + i2u(writeChar, v);
}

int gvprintf(writeCharFunc writeChar, char *fmt, va_list ap) {
	int len = 0;
	while(*fmt) {
		if (*fmt == '%') {
			uint8_t size = 2; // default size
			uint32_t mask = 0xFFFF;
			char f = 'd'; // default type
			fmt++;

			switch(*fmt) {
			case '1':
				size = 1;
				fmt++;
				break;
			case '2':
				size = 2;
				fmt++;
				break;
			case '4':
				size = 4;
				fmt++;
				break;
			}
			switch(*fmt) {
			case '%':
				outputChar(*fmt);
				break;
			case 's':
				{
					char *s = va_arg (ap, char *);
					while(*s) {
						outputChar(*s++);
					}
				}
				break;
			case 'S':
				{
					char *s = va_arg (ap, char *);
					char c;
					while((c = pgm_read_byte(s)) != '\0') {
						outputChar(c);
						s++;
					}
				}
				break;
			case 'c':
				{
					unsigned char c = (unsigned char)va_arg (ap, int /*char*/);
					outputChar(c);
				}
				break;
			case 'u':
			case 'd':
			case 'x':
			case 'b':
				{
					uint32_t v;
					switch (size) {
					case 1:
						v = va_arg (ap, int/*uint8_t*/);
						break;
					case 2:
						v = va_arg (ap, int/*uint16_t*/);
						break;
					case 4:
						v = va_arg (ap, uint32_t);
						break;
					}
					if (*fmt == 'x') {
						len += i2h(writeChar, v, size);
					} else if (*fmt == 'b') {
						len += i2b(writeChar, v, size);
					} else {
						len += i2d(writeChar, v, size, *fmt == 'd');
					}
				}
				break;
			default:
				outputChar(*fmt);
				break;
			}
			fmt++;
		} else {
			outputChar(*fmt);
			fmt++;
		}
	}
	return len;
}
