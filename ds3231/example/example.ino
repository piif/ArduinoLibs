#include <Arduino.h>

#if defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny25__)
	#define ARDUINO_TINY
#elif defined(__AVR_MEGA__)
	#define ARDUINO_UNO
    #define HAVE_SERIAL
#endif

#ifdef ARDUINO_UNO
    #define DS_SQW A3
#else
    #define DS_SQW 1
    #define DEBUG_PORT 3
#endif

#include "ds3231.h"
#include "timeFunctions.h"


DS3231 rtc;

#if defined DEBUG_PORT
void dumpByte(byte value) {
    for(byte mask = 0x80 ; mask >>= 1; mask) {
        digitalWrite(DEBUG_PORT, (value & mask) != 0);
    }
}
#endif

void displayTime() {
    TimeStruct time;
    rtc.getTime(&time);
    toLocal(&time);
#ifdef HAVE_SERIAL
    Serial.print("dayOfWeek : "); Serial.print(time.dayOfWeek);
    const char *dayOfWeek = (char *)pgm_read_word(&(shortDays[time.dayOfWeek]));
    Serial.print(" = ");
    while (char c=pgm_read_byte(dayOfWeek++)) {
        Serial.print(c);
    }
    Serial.println();
    Serial.print("dayOfMonth: "); Serial.println(time.dayOfMonth);
    Serial.print("month     : "); Serial.print(time.month);
    const char *month = (char *)pgm_read_word(&(shortMonthes[time.month]));
    Serial.print(" = ");
    while (char c=pgm_read_byte(month++)) {
        Serial.print(c);
    }
    Serial.println();
    Serial.print("year      : "); Serial.println(time.year);
    Serial.print("hours     : "); Serial.println(time.hours);
    Serial.print("minutes   : "); Serial.println(time.minutes);
    Serial.print("seconds   : "); Serial.println(time.seconds);

    float fullTemp = rtc.getFullTemp() / 4.0;
    short temp = rtc.getShortTemp();
    Serial.print("full temp : "); Serial.println(fullTemp);
    Serial.print("temp      : "); Serial.println(temp);
#elif defined DEBUG_PORT
    dumpByte(0x7E);
    dumpByte(time.year);
    dumpByte(time.month);
    dumpByte(time.dayOfMonth);
    dumpByte(time.dayOfWeek);
    dumpByte(time.hours);
    dumpByte(time.minutes);
    dumpByte(time.seconds);
    dumpByte(0x7E);
#endif
}

void setup() {
#ifdef HAVE_SERIAL
    Serial.begin(115200);
#endif

#ifdef ARDUINO_UNO
   // // initialize external interrupt on raising edge of pin 2 (INT0)
    // EICRA |= 0x03;
    // EIMSK |= 1 << INT0;

    // initialize external interrupt on pin A3 (PCINT11)
    PCMSK1 |= 1 << PCINT11;
    PCICR  |= 1 << PCIE1;
#endif

// #ifdef ARDUINO_TINY
//     TCCR1 = 0;
// #endif

#if defined DEBUG_PORT
    pinMode(DEBUG_PORT, OUTPUT);
#endif

// #define INITIALIZE TRUE
#ifdef INITIALIZE
    TimeStruct time = {
        00, /* seconds */
        10, /* minutes */
        22, /* hours */
         6, /* dayOfWeek */
        25, /* dayOfMonth */
         3, /* month */
        23  /* year */
    };
    rtc.setTime(&time);

    /* output square wave + oscillator continue counting when power off + no oscillator output */
    rtc.setControl(0b00000000 , 0b10000000);
    /* output nothing */
    // setControl(0b10000100 , 0b10000000);
    /* output nothing but continue counting */
    // setControl(0b00000100 , 0b10001000);
#endif

#if define HAVE_SERIAL && defined DEBUG_DS3231
    Serial.println("dumpAllRegisters :");
    rtc.dumpAllRegisters();
#endif

#ifdef HAVE_SERIAL
    Serial.println("Setup OK");
#endif
}

#ifdef ARDUINO_UNO
volatile bool clockTick = 0;

// ISR(INT0_vect) {
//     clockTick = 1;
// }
ISR(PCINT1_vect) {
    clockTick = digitalRead(DS_SQW);
}

void loop() {
    if (clockTick) {
        displayTime();
        clockTick = 0;
    }
}
#else
void loop() {
    displayTime();
}
#endif
