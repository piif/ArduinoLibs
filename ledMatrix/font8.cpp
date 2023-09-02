#include <Arduino.h>
#include <avr/pgmspace.h>

#define FONT8_CPP

#include <font8.h>

#if defined THIN_FONT
#include <font8thin.h>
#elif defined WIDE_FONT
#include <font8wide.h>
#elif defined USER_FONT
// font is defined by main program Which must define following function
extern const byte *getCharMap(char c);
#else
#error Must define THIN_FONT, WIDE_FONT or USER_FONT
#endif

// return width of character from map
byte charWidth(const byte * map) {
    if (map == NULL) {
        return 0;
    }
    return pgm_read_byte_near(map + 8);
}

// return width of character from char
byte charWidth(char c) {
    const byte *map = getCharMap(c);
    return  charWidth(map);
}

// Given an array of 8xN bytes containing 8 lines (top to bottom) of N bytes (left to right) of 8 bits (MSB = left, LSB = right)
// Draw a char into the array, at position X (thus from bit 8-X%8 into byte X/8 of each line)
// return next X position (Depends on character width)
int drawChar(byte *matrix, byte width, int X, char c) {
    const byte *map = getCharMap(c);
    if (map == NULL) {
        return X;
    }
    byte cw = charWidth(map);
    if (cw == 0) {
        return X;
    }

    byte lineOffset = X / 8;
    if (lineOffset >= width) {
        return X;
    }
    byte bitOffset = X & 7;
    // don't overlap if it's over the last matrix
    bool overlap = cw + bitOffset > 8;
    int newX = X + cw;
    if (newX >= width*8) {
        overlap = false;
        newX = width*8;
    }

    byte *ptr = matrix + lineOffset;
    for(byte y=0; y<8; y++) {
        byte mapRow = pgm_read_byte_near(map + y);
        ptr[0] |= mapRow >> bitOffset;
        if (overlap) {
            ptr[1] |= mapRow << (8 - bitOffset);
        }
        ptr += width;
    }
    return newX;
}

int drawString(byte *matrix, byte width, int X, const char *str) {
    for(;;) {
        if (!*str) {
            return X;
        }
        X = drawChar(matrix, width, X, *str);
        if (X >= width*8) {
            return width*8;
        }
        str++;
    }
}

void drawStringRight(byte *matrix, byte width, const char *str) {
    if (!*str) {
        return;
    }

    const char *ptr = str;
    // seek to last char
    while(*ptr++);
    ptr--;

    int x = width * 8 - 1;
    while(ptr >= str) { // go back until start of string
        byte w = charWidth(*ptr);
        if (x < w) {
            break;
        }
        drawChar(matrix, width, x - w, *ptr);
        x -= w;
        ptr--;
    }
}

// Draw vertical char from position Y (0=top)
void drawVChar(byte *matrix, byte height, int Y, char c) {
    if (Y >= height) {
        return;
    }
    const byte *map = getCharMap(c);
    byte cw = charWidth(map);
    if (cw == 0) {
        return;
    }
    byte offset = (8-cw)/2;

    // Serial.print("drawVChar '");Serial.print(c);Serial.print("' @ ");Serial.print(Y);Serial.print('/');Serial.println(height);
    byte *ptr = matrix + Y;
    // Serial.print("ptr=");Serial.println(ptr-matrix);
    for(byte row=0, rowMask = 0x80; row<8; row++, rowMask >>=1) {
        byte mapRow = pgm_read_byte_near(map + row) >> offset;
        for(byte col=0, colMask=0x01; col<8; col++, colMask <<= 1) {
            if (mapRow & colMask) {
                ptr[height*col] |= rowMask;
            }
        }
    }
}

// Draw vertical string from position Y (0=top), descending
void drawVString(byte *matrix, byte height, int Y, const char *str) {
    for (byte y = Y; *str && y < height; y++) {
        drawVChar(matrix, height, y, *str);
    }
}
