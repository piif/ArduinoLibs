// arduino tools chain includes eveything ...
// => force include only from inside font7.cpp
#ifdef FONT8_CPP
#define SPACE_WIDTH 1

// Numeric Font Matrix (Arranged as 8x font data + 1x kerning data)
// ascii chars from 0x20 (space) to 0x7F (°)
const byte font [] PROGMEM = {
#ifndef REDUCED_MAP
    0b00000000, //Space (Char 0x20)
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    SPACE_WIDTH,

    0b10000000, //!
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b10000000,
    0b00000000,
    2,

    0b10100000, //"
    0b10100000,
    0b10100000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    4,

    0b01010000, //#
    0b01010000,
    0b11111000,
    0b01010000,
    0b11111000,
    0b01010000,
    0b01010000,
    0b00000000,
    6,

    0b00100000, //$
    0b01111000,
    0b10100000,
    0b01110000,
    0b00101000,
    0b11110000,
    0b00100000,
    0b00000000,
    6,

    0b11000000, //%
    0b11001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10011000,
    0b00011000,
    0b00000000,
    6,

    0b01100000, //&
    0b10010000,
    0b10100000,
    0b01000000,
    0b10101000,
    0b10010000,
    0b01101000,
    0b00000000,
    6,

    0b11000000, //'
    0b01000000,
    0b10000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    3,

    0b00000000, //(
    0b00100000,
    0b01000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b01000000,
    0b00100000,
    4,

    0b00000000, //)
    0b10000000,
    0b01000000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b01000000,
    0b10000000,
    4,

    0b00000000, //*
    0b00100000,
    0b10101000,
    0b01110000,
    0b10101000,
    0b00100000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //+
    0b00100000,
    0b00100000,
    0b11111000,
    0b00100000,
    0b00100000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11000000,
    0b01000000,
    0b10000000,
    3,

    0b00000000, //-
    0b00000000,
    0b00000000,
    0b11111000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //.
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11000000,
    0b11000000,
    0b00000000,
    3,

    0b00000000, ///
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b00000000,
    0b00000000,
    6,
#endif
    0b01100000, //0 (Char 0x30)
    0b10010000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b01100000,
    0b00000000,
    5,

    0b01000000, //1
    0b11000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b00000000,
    3,

    0b01100000, //2
    0b10010000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b11110000,
    0b00000000,
    5,

    0b01100000, //3
    0b10010000,
    0b00010000,
    0b01100000,
    0b00010000,
    0b10010000,
    0b01100000,
    0b00000000,
    5,

    0b00010000, //4
    0b00100000,
    0b01000000,
    0b10000000,
    0b10010000,
    0b11110000,
    0b00010000,
    0b00000000,
    5,
 
    0b11110000, //5
    0b10000000,
    0b10000000,
    0b01100000,
    0b00010000,
    0b10010000,
    0b01100000,
    0b00000000,
    5,

    0b01100000, //6
    0b10010000,
    0b10000000,
    0b11100000,
    0b10010000,
    0b10010000,
    0b01100000,
    0b00000000,
    5,

    0b11110000, //7
    0b00010000,
    0b00010000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b00000000,
    5,

    0b01100000, //8
    0b10010000,
    0b10010000,
    0b01100000,
    0b10010000,
    0b10010000,
    0b01100000,
    0b00000000,
    5,

    0b01100000, //9
    0b10010000,
    0b10010000,
    0b01110000,
    0b00010000,
    0b00010000,
    0b11100000,
    0b00000000,
    5,

    0b00000000, //:
    0b00000000,
    0b00000000,
    0b10000000,
    0b00000000,
    0b10000000,
    0b00000000,
    0b00000000,
    2,

    0b00000000, //;
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    0b01000000,
    0b10000000,
    0b00000000,
    3,

    0b00010000, //<
    0b00100000,
    0b01000000,
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00000000,
    5,

    0b00000000, //=
    0b00000000,
    0b00000000,
    0b11111000,
    0b00000000,
    0b11111000,
    0b00000000,
    0b00000000,
    6,

    0b10000000, //>
    0b01000000,
    0b00100000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b00000000,
    5,

    0b01110000, //?
    0b10001000,
    0b00001000,
    0b00010000,
    0b00100000,
    0b00000000,
    0b00100000,
    0b00000000,
    6,

#ifndef REDUCED_MAP
    0b01110000, //@ (Char 0x40)
    0b10001000,
    0b00001000,
    0b01101000,
    0b10101000,
    0b10101000,
    0b01110000,
    0b00000000,
    6,

    0b01110000, //A
    0b10001000,
    0b10001000,
    0b11111000,
    0b10001000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b11110000, //B
    0b10001000,
    0b11110000,
    0b10001000,
    0b10001000,
    0b11110000,
    0b00000000,
    0b00000000,
    6,

    0b01110000, //C
    0b10001000,
    0b10000000,
    0b10000000,
    0b10001000,
    0b01110000,
    0b00000000,
    0b00000000,
    6,

    0b11100000, //D
    0b10010000,
    0b10001000,
    0b10001000,
    0b10010000,
    0b11100000,
    0b00000000,
    0b00000000,
    6,

    0b11111000, //E
    0b10000000,
    0b11110000,
    0b10000000,
    0b10000000,
    0b11111000,
    0b00000000,
    0b00000000,
    6,

    0b11111000, //F
    0b10000000,
    0b11110000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b00000000,
    6,

    0b01110000, //G
    0b10001000,
    0b10000000,
    0b10111000,
    0b10001000,
    0b01111000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //H
    0b10001000,
    0b11111000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b11100000, //I
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b11100000,
    0b00000000,
    0b00000000,
    4,

    0b00111000, //J
    0b00010000,
    0b00010000,
    0b00010000,
    0b10010000,
    0b01100000,
    0b00000000,
    0b00000000,
    6,

    0b10010000, //K
    0b10100000,
    0b11000000,
    0b10100000,
    0b10010000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b10000000, //L
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b11111000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //M
    0b11011000,
    0b10101000,
    0b10101000,
    0b10001000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //N
    0b11001000,
    0b10101000,
    0b10011000,
    0b10001000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b01110000, //O
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b01110000,
    0b00000000,
    0b00000000,
    6,

    0b11110000, //P
    0b10001000,
    0b10001000,
    0b11110000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b00000000,
    6,

    0b01110000, //Q
    0b10001000,
    0b10001000,
    0b10101000,
    0b10010000,
    0b01101000,
    0b00000000,
    0b00000000,
    6,

    0b11110000, //R
    0b10001000,
    0b10001000,
    0b11110000,
    0b10010000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b01111000, //S
    0b10000000,
    0b01110000,
    0b00001000,
    0b00001000,
    0b11110000,
    0b00000000,
    0b00000000,
    6,

    0b11111000, //T
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //U
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b01110000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //V
    0b10001000,
    0b10001000,
    0b10001000,
    0b01010000,
    0b00100000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //W
    0b10001000,
    0b10001000,
    0b10101000,
    0b10101000,
    0b01010000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //X
    0b10001000,
    0b01010000,
    0b00100000,
    0b01010000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b10001000, //Y
    0b10001000,
    0b01010000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00000000,
    0b00000000,
    6,

    0b11111000, //Z
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b11111000,
    0b00000000,
    0b00000000,
    6,

    0b11100000, //[
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b11100000,
    0b00000000,
    4,

    0b00000000, //(Backward Slash)
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000000,
    0b00000000,
    6,

    0b11100000, //]
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b11100000,
    0b00000000,
    4,

    0b00100000, //^
    0b01010000,
    0b10001000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //_
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b11111000,
    6,
#endif
    0b10000000, //` (Char 0x60)
    0b01000000,
    0b00100000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    4,

    0b00000000, //a
    0b11100000,
    0b00010000,
    0b01110000,
    0b10010000,
    0b01110000,
    0b00000000,
    0b00000000,
    5,

    0b10000000, //b
    0b10000000,
    0b11100000,
    0b10010000,
    0b10010000,
    0b01100000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //c
    0b01100000,
    0b10010000,
    0b10000000,
    0b10010000,
    0b01100000,
    0b00000000,
    0b00000000,
    5,

    0b00010000, //d
    0b00010000,
    0b01110000,
    0b10010000,
    0b10010000,
    0b01100000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //e
    0b01100000,
    0b10010000,
    0b11110000,
    0b10000000,
    0b01110000,
    0b00000000,
    0b00000000,
    5,

    0b01100000, //f
    0b10010000,
    0b10000000,
    0b11000000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //g
    0b01100000,
    0b10010000,
    0b10010000,
    0b01110000,
    0b00010000,
    0b00010000,
    0b11100000,
    5,

    0b10000000, //h
    0b10000000,
    0b11100000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b00000000,
    0b00000000,
    5,

    0b10000000, //i
    0b00000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b00000000,
    2,

    0b00100000, //j
    0b00000000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b10100000,
    0b01000000,
    4,

    0b10000000, //k
    0b10000000,
    0b10110000,
    0b11000000,
    0b10100000,
    0b10010000,
    0b00000000,
    0b00000000,
    5,

    0b10000000, //l
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b01000000,
    0b00000000,
    0b00000000,
    3,

    0b00000000, //m
    0b11010000,
    0b10101000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //n
    0b10100000,
    0b11010000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //o
    0b01100000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b01100000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //p
    0b01100000,
    0b10010000,
    0b10010000,
    0b11100000,
    0b10000000,
    0b10000000,
    0b10000000,
    5,

    0b00000000, //q
    0b01100000,
    0b10010000,
    0b10010000,
    0b01110000,
    0b00010000,
    0b00010000,
    0b00010000,
    5,

    0b00000000, //r
    0b10100000,
    0b11010000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //s
    0b01110000,
    0b10000000,
    0b01100000,
    0b00010000,
    0b11100000,
    0b00000000,
    0b00000000,
    5,

    0b01000000, //t
    0b11100000,
    0b01000000,
    0b01000000,
    0b01010000,
    0b00100000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //u
    0b10010000,
    0b10010000,
    0b10010000,
    0b10010000,
    0b01110000,
    0b00000000,
    0b00000000,
    5,

    0b00000000, //v
    0b10001000,
    0b10001000,
    0b10001000,
    0b01010000,
    0b00100000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //w
    0b10001000,
    0b10001000,
    0b10001000,
    0b10101000,
    0b01010000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //x
    0b10001000,
    0b01010000,
    0b00100000,
    0b01010000,
    0b10001000,
    0b00000000,
    0b00000000,
    6,

    0b00000000, //y
    0b10010000,
    0b10010000,
    0b10010000,
    0b01110000,
    0b00010000,
    0b00010000,
    0b01100000,
    5,

    0b00000000, //z
    0b11110000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b11110000,
    0b00000000,
    0b00000000,
    5,

    0b00100000, //{
    0b01000000,
    0b01000000,
    0b10000000,
    0b01000000,
    0b01000000,
    0b00100000,
    0b00000000,
    4,

    0b10000000, //|
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    2,

    0b10000000, //}
    0b01000000,
    0b01000000,
    0b00100000,
    0b01000000,
    0b01000000,
    0b10000000,
    0b00000000,
    4,

    0b00000000, //~
    0b00000000,
    0b01101000,
    0b10010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    6,

    0b01100000, //° (Char 0x7F)
    0b10010000,
    0b10010000,
    0b01100000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    5
};
#endif