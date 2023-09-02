#ifndef FONT8_H
#define FONT8_H

#include <Arduino.h>

// return width of character
byte charWidth(char c);

// Given an array of 8xN bytes containing N matrices (left to right) of 8 bytes (top to bottom) of 8 bits (LSB = right)
// Draw a char into the array, at position X (thus from bit 8-X%8 into matrix X/8)
// return next X position (Depends on character width)
int drawChar(byte *matrix, byte width, int X, char c);

int drawString(byte *matrix, byte width, int X, const char *str);

void drawStringRight(byte *matrix, byte width, const char *str);

// Draw vertical char from position Y (0=top)
void drawVChar(byte *matrix, byte height, int Y, char c);
// Draw vertical string from position Y (0=top), descending
void drawVString(byte *matrix, byte height, int Y, const char *str);

#endif