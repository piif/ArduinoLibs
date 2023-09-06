#include <Arduino.h>
#include "timeFunctions.h"

const byte lastDay[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const char null_str[] PROGMEM = "";
const char shortDay1[] PROGMEM = "lun";
const char shortDay2[] PROGMEM = "mar";
const char shortDay3[] PROGMEM = "mer";
const char shortDay4[] PROGMEM = "jeu";
const char shortDay5[] PROGMEM = "ven";
const char shortDay6[] PROGMEM = "sam";
const char shortDay7[] PROGMEM = "dim";

const char * const shortDays[] PROGMEM = {
    null_str,
    shortDay1,
    shortDay2,
    shortDay3,
    shortDay4,
    shortDay5,
    shortDay6,
    shortDay7
};

const char shortMonth1 [] PROGMEM = "jan";
const char shortMonth2 [] PROGMEM = "fev";
const char shortMonth3 [] PROGMEM = "mar";
const char shortMonth4 [] PROGMEM = "avr";
const char shortMonth5 [] PROGMEM = "mai";
const char shortMonth6 [] PROGMEM = "juin";
const char shortMonth7 [] PROGMEM = "juil";
const char shortMonth8 [] PROGMEM = "aou";
const char shortMonth9 [] PROGMEM = "sep";
const char shortMonth10[] PROGMEM = "oct";
const char shortMonth11[] PROGMEM = "nov";
const char shortMonth12[] PROGMEM = "dec";

const char * const shortMonthes[] PROGMEM = {
    null_str,
    shortMonth1,
    shortMonth2,
    shortMonth3,
    shortMonth4,
    shortMonth5,
    shortMonth6,
    shortMonth7,
    shortMonth8,
    shortMonth9,
    shortMonth10,
    shortMonth11,
    shortMonth12
};

byte lastDayOfMonth(byte month, byte year) {
    byte last = lastDay[month];
    if (month == 2 && year%4 == 0) {
        return last+1; // correct from 1901 to 2099, should be enough ;-)
    } else {
        return last;
    }
}

// returns :
// 4 if day only changed
// 5 if month changed
// 6 if year changed
byte nextDay(TimeStruct *time) {
    if (time->dayOfWeek == 7) {
        time->dayOfWeek = 1;
    } else {
        time->dayOfWeek++;
    }
    byte last = lastDayOfMonth(time->month, time->year);
    if (time->dayOfMonth == last) {
        time->dayOfMonth = 1;
        if (time->month == 12) {
            time->year++;
            time->month = 1;
            return 3;
        } else  {
            time->month++;
            return 2;
        }
    } else {
        time->dayOfMonth++;
        return 1;
    }
}

// returns :
// 4 if day only changed
// 5 if month changed
// 6 if year changed
byte prevDay(TimeStruct *time) {
    if (time->dayOfWeek == 1) {
        time->dayOfWeek = 7;
    } else {
        time->dayOfWeek--;
    }

    if (time->dayOfMonth != 1) {
        time->dayOfMonth--;
        return 1;
    } else {
        // first day of month -> compute prev month , then deduce last day of month
        if (time->month == 1) {
            time->month = 12;
            time->year--;
            time->dayOfMonth = lastDayOfMonth(time->month, time->year);
            return 3;
        } else {
            time->month--;
            time->dayOfMonth = lastDayOfMonth(time->month, time->year);
            return 2;
        }
    }
}

// return +1 or +2 according to Paris timezone DST
byte getOffset(TimeStruct *time) {
    byte dayOfWeek = time->dayOfWeek % 7; // convert to 0(sunday)-6(saturday) value
    if (
        ( time->month > 3 && time->month < 10 ) // from april to september
            ||
        ( // after last synday of march
            ( time->month == 3 && (time->dayOfMonth - dayOfWeek) >= 25 )
                &&
            ! ( time->dayOfMonth >= 25 && dayOfWeek == 0 )
        )
            ||
        ( // before last sunday of october
            ( time->month == 10 && (time->dayOfMonth - dayOfWeek) < 25 )
                &&
            ! ( time->dayOfMonth >= 25 && dayOfWeek == 0 )
        )
            ||
        ( // on last sunday of october before 1:00 AM , or of april after 0:00
            ( (time->month == 10 && time->hours < 1) || (time->month == 3 && time->hours > 0) )
                &&
            ( time->dayOfMonth >= 25 && dayOfWeek == 0 )
        )
    ) {
        return 2;
    }
    return 1;
}

// returns :
// 3 if hours changed
// 4 if day only changed
// 5 if month changed
// 6 if year changed
byte toLocal(TimeStruct *time) {
    byte offset = getOffset(time);

    time->hours += offset;
    if (time->hours > 23) {
        time->hours -= 24;
        return 1+nextDay(time);
    }
    return 1;
}

// returns :
// 3 if hours changed
// 4 if day only changed
// 5 if month changed
// 6 if year changed
byte fromLocal(TimeStruct *time) {
    byte offset = getOffset(time);
    if (time->hours >= offset) {
        time->hours -= offset;
        return 1;
    } else {
        time->hours += 24-offset;
        return 1+prevDay(time);
    }
}

// returns :
// 1 if seconds only changed
// 2 if minutes changed
// 3 if hours changed
// 4 if day only changed
// 5 if month changed
// 6 if year changed
byte incrementSecond(TimeStruct *time) {
    if (time->seconds < 59) {
        time->seconds++;
        return 1;
    }
    time->seconds=0;
    if (time->minutes < 59) {
        time->minutes++;
        return 2;
    }
    time->minutes=0;
    if (time->hours < 23) {
        time->hours++;
        return 3;
    }
    time->hours=0;
    return 3 + nextDay(time);
}
