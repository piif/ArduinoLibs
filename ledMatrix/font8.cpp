#include <Arduino.h>
#include <avr/pgmspace.h>

#define FONT8_CPP

#include <font8.h>

#ifdef THIN_FONT
#include <font8thin.h>
#else
#include <font8wide.h>
#endif

#ifdef REDUCED_MAP
    #define CHAR_POS(c) ( ((c) >= 0x60) ? ((c) - 0x50) : ((c) - 0x30) ) 
#else
    #define CHAR_POS(c) ((c) - 0x20) 
#endif

// return width of character
byte charWidth(char c) {
#ifdef REDUCED_MAP
    if (c == 0x20) {
        return SPACE_WIDTH;
    }
    if (c < 0x30 || (c >= 0x40 && c < 0x60)) {
        return 0;
    }
#else
    if (c < 0x20 || c > 0x7F) {
        return 0;
    }
#endif
    return pgm_read_byte_near(font + (CHAR_POS(c) * 9) + 8);
}

// Given an array of 8xN bytes containing 8 lines (top to 0bottom) of N bytes (left to right) of 8 0bits (MSB = left, LSB = right)
// Draw a char into the array, at position X (thus from 0bit 8-X%8 into byte X/8 of each line)
// return next X position (Depends on character width)
int drawChar(byte *matrix, byte width, int X, char c) {
    byte cw = charWidth(c);
    if (cw == 0) {
        return X;
    }
#ifdef REDUCED_MAP
    if (c == ' ') {
        return X + SPACE_WIDTH;
    }
#endif 
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
    const byte *fontChar = font + (CHAR_POS(c) * 9);
    for(byte y=0; y<8; y++) {
        byte map = pgm_read_byte_near(fontChar + y);
        ptr[0] |= map >> bitOffset;
        if (overlap) {
            ptr[1] |= map << (8 - bitOffset);
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
