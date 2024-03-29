#include <Arduino.h>
#include "ledMatrix.h"
#include "font8.h"

LedMatrix::LedMatrix() {
    // caller must call setup after instanciation
}

LedMatrix::LedMatrix(byte _width, byte _clk, byte _cs, byte _din, byte intensity) {
    setup(_width, _clk, _cs, _din, intensity);
}

void LedMatrix::setup(byte _width, byte _clk, byte _cs, byte _din, byte intensity) {
    width = _width;
    clk = _clk;
    cs = _cs;
    din = _din;

    matrix = new byte[8 * width];

    pinMode(clk, OUTPUT);
    pinMode(cs , OUTPUT);
    pinMode(din, OUTPUT);
    digitalWrite(cs , LOW);
    digitalWrite(clk, HIGH);

    clear();

    sendCommand(0xF, 0, width); // normal mode
    sendCommand(0x9, 0, width); // clear decode mode
    sendCommand(0xA, intensity, width); // set intensity
    sendCommand(0xB, 7, width); // set scan limit
    sendCommand(0xC, 1, width); // clear shutdown 
}

void LedMatrix::sendCommand(byte address, byte value, byte iterations) {
#ifdef HAVE_SERIAL
    Serial.print(address, HEX); Serial.print(' '); Serial.println(value, BIN);
#endif
    pinMode(din, OUTPUT);

    while(iterations--) {
        shiftOut(din, clk, MSBFIRST, address); 
        shiftOut(din, clk, MSBFIRST, value); 
    }
    digitalWrite(cs, HIGH);
    digitalWrite(cs, LOW);
}

void LedMatrix::sendData(byte address, byte *values, byte len) {
#ifdef HAVE_SERIAL
    Serial.print(address, HEX); 
    for (byte i=0; i<len; i++) {
        Serial.print(' '); Serial.print(values[i], BIN);
    }
    Serial.println();
#endif
    pinMode(din, OUTPUT);

    if (inverted) {
        do {
            len--;
            shiftOut(din, clk, MSBFIRST, address);
            shiftOut(din, clk, LSBFIRST, values[len]);
        } while(len);
    } else {
        while(len--) {
            shiftOut(din, clk, MSBFIRST, address);
            shiftOut(din, clk, MSBFIRST, *values);
            values++;
        }
    }

    digitalWrite(cs, HIGH);
    digitalWrite(cs, LOW);
}

void LedMatrix::setIntensity(byte intensity) {
    sendCommand(0xA, intensity, width);
}

void LedMatrix::clear() {
    memset(matrix, 0, 8*width);
}

void LedMatrix::flush() {
    byte *ptr = matrix;
    if (inverted) {
        for(byte y=8; y>=1; y--) {
            sendData(y, ptr, width);
            ptr += width;
        }
    } else {
        for(byte y=1; y<=8; y++) {
            sendData(y, ptr, width);
            ptr += width;
        }
    }
}

byte LedMatrix::charWidth(char c) {
    return ::charWidth(c);
}

byte LedMatrix::stringWidth(char *str) {
    byte len = 0;
    while (*str) {
        len += ::charWidth(*str++);
    }
    return len;
}

// Given an array of 8xN bytes containing N matrices (left to right) of 8 bytes (top to bottom) of 8 bits (LSB = right)
// Draw a char into the array, at position X (thus from bit 8-X%8 into matrix X/8)
// return next X position (Depends on character width)
int LedMatrix::drawChar(int X, char c) {
    return ::drawChar(matrix, width, X, c);
}

int LedMatrix::drawString(int X, const char * str) {
    return ::drawString(matrix, width, X, str);
}
int LedMatrix::drawString_P(int X, const char * const str) {
    const char *ptr = str;
    while(char c = pgm_read_byte(ptr++)) {
        X = ::drawChar(matrix, width, X, c);
    }
    return X;
}

void LedMatrix::drawPixel(int X, int Y, bool value) {
    byte lineOffset = X / 8;
    if (lineOffset >= width || Y > 7) {
        return;
    }
    byte bitOffset = X & 7;
    byte *ptr = matrix + Y*width + lineOffset;
    if (value) {
        *ptr |= 0x80 >> bitOffset;
    } else {
        *ptr &= ~(0x80 >> bitOffset);
    }
}

void LedMatrix::drawStringRight(const char *str) {
    ::drawStringRight(matrix, width, str);
}

void LedMatrix::drawVChar(int Y, char c) {
    ::drawVChar(matrix, width, Y, c);
}
void LedMatrix::drawVString(int Y, const char *str) {
    ::drawVString(matrix, width, Y, str);
}

void LedMatrix::dumpMatrix(Stream &stream) {
    for(byte y=0; y<8; y++) {
        for(byte x=0; x<width; x++) {
            byte b = matrix[x+y*width];
            for(byte mask = 0x80; mask; mask >>= 1) {
                stream.print(b & mask ? '#' : ' ');
            }
        }
        stream.println();
    }
}
