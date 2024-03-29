#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>

// test MAX7219 chained led matrix 8x8xN

#ifdef ARROWS_MAP
#define ARROW_UP    '{'
#define ARROW_DOWN  '|'
#define ARROW_LEFT  '}'
#define ARROW_RIGHT '~'
#endif

class LedMatrix {
public:
    bool inverted = false;

    LedMatrix();
    LedMatrix(byte _width, byte _clk, byte _cs, byte _din, byte intensity = 2);

    void setup(byte _width, byte _clk, byte _cs, byte _din, byte intensity = 2);

    void sendCommand(byte address, byte value, byte iterations = 1);

    void sendData(byte address, byte *values, byte len);
    
    void setIntensity(byte intensity);

    void clear();
    
    void flush();

    byte charWidth(char c);
    byte stringWidth(char *str);

    int drawChar(int X, char c);
    int drawString(int X, const char * str);
    int drawString_P(int X, const char * const str);

    void drawPixel(int X, int Y, bool value);
    void drawStringRight(const char *str);

    void drawVChar(int Y, char c);
    void drawVString(int Y, const char *str);

    void dumpMatrix(Stream &stream);

private:
    byte width;
    byte clk, cs, din;
    byte *matrix;
};

#endif