#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>

// test MAX7219 chained led matrix 8x8xN

class LedMatrix {
public:
    LedMatrix(byte _width, byte _clk, byte _cs, byte _din, byte intensity = 2);

    void setup(byte intensity = 2);

    void sendCommand(byte address, byte value, byte iterations = 1);

    void sendData(byte address, byte *values, byte len);
    
    void setIntensity(byte intensity);

    void clear();
    
    void flush();

    byte charWidth(char c);
    byte stringWidth(char *str);

    int drawChar(int X, char c);
    int drawString(int X, char *str);
    void drawPixel(int X, int Y, bool value);

    void dumpMatrix(Stream &stream);

private:
    byte width;
    byte clk, cs, din;
    byte *matrix;
};

#endif