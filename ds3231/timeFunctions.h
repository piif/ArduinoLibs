#ifndef TIMEFUNTIONS_H
#define TIMEFUNTIONS_H

#ifdef ARDUINO
#include <Arduino.h>
#endif
typedef struct _TimeStruct {
    byte seconds;    /* 00 - 59 */
    byte minutes;    /* 00 - 59 */
    byte hours;      /* 00 - 23 */
    byte dayOfWeek;  /*  1 (monday) -  7 (sunday) */
    byte dayOfMonth; /*  1 - 31 */
    byte month;      /*  1 - 12 */
    byte year;       /*  0 - 99 */
} TimeStruct;

extern const char * const shortDays[] PROGMEM;
extern const char * const shortMonthes[] PROGMEM;

// last day of given month, including lap year
byte lastDayOfMonth(byte month, byte year);

// convert UTC time to France local time with DST
byte toLocal(TimeStruct *time);
// France DST to UTC
byte fromLocal(TimeStruct *time);

// add 1 second to time struct, cascading to minutes, ... year if needed
byte incrementSecond(TimeStruct *time);

#endif