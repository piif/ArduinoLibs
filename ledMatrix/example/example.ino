#include <Arduino.h>

#include "ledMatrix.h"

// test MAX7219 chained led matrix 8x8xN

#if defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny25__)
	#define ARDUINO_TINY
#elif defined(__AVR_MEGA__)
	#define ARDUINO_UNO
    #define HAVE_SERIAL
#endif

#ifdef ARDUINO_UNO
    #define MATRIX_CLK A2
    #define MATRIX_CS  A1
    #define MATRIX_DIN 7 // A4
#else
    #define MATRIX_CLK 1
    #define MATRIX_CS  4
    #define MATRIX_DIN 3 // 0
#endif

#define WIDTH 12

LedMatrix ledMatrix(WIDTH, MATRIX_CLK, MATRIX_CS, MATRIX_DIN, 2);

byte testBuffer[] = {
    // 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x81
    0x03, 0x0C, 0x30, 0xC0, 0x11, 0x22, 0x44, 0x88
};

const char pgmStr[] PROGMEM = "progmem string";

void setup() {
#ifdef HAVE_SERIAL
    Serial.begin(115200);
    Serial.println("Setup start");
#endif

#ifdef HAVE_SERIAL
    delay(1000);
    Serial.println("send testBuffer");
#endif
    for (byte i=0; i<8; i++) {
        ledMatrix.sendCommand(i+1, testBuffer[i], WIDTH);
    }

    delay(1000);

#ifdef HAVE_SERIAL
    Serial.println("draw pgmStr");
#endif
    ledMatrix.clear();
    ledMatrix.drawString_P(1, pgmStr);
    ledMatrix.flush();

    delay(1000);

#ifdef HAVE_SERIAL
    Serial.println("Setup OK");
#endif
}

char buffer[25];
byte i = 0;

void loop() {
#ifdef HAVE_SERIAL
    if (i >= 25) {
        i = 0;
    }
    int c = Serial.read();
    if (c == -1) {
        return;
    }
    if (c == '\n' || c == '\r') {
        buffer[i] = 0;
        Serial.print("[");Serial.print(buffer);Serial.println("]");
        ledMatrix.clear();
        ledMatrix.drawString(0, buffer);
#ifdef HAVE_SERIAL
        ledMatrix.dumpMatrix(Serial);
#endif
        ledMatrix.flush();
        i = 0;
        return;
    }
    buffer[i] = c;
    i++;
#else
    static byte ascii=0;

    delay(1000);

    for (byte i=0; i<24; i++) {
        buffer[i] = ascii+20+i;
    }
    buffer[24] = '\0';
    ascii= (ascii + 15) % 108; // char table contains values from 20 to 127

    ledMatrix.setup();
    ledMatrix.drawString(0, buffer);
    ledMatrix.flush();
#endif
}
