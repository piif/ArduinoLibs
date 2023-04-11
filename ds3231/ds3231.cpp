#define HAVE_SERIAL

#include <Arduino.h>
#ifdef ARDUINO_attiny
    #include "TinyWireM.h"
    #define I2C TinyWireM
#else
    #include <Wire.h>
    #define I2C Wire
#endif
#include "ds3231.h"

DS3231::DS3231() {
    //I2C.begin();
}

#ifdef DS3231_DEBUG
void DS3231::dumpAllRegisters() {
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(0);
    I2C.endTransmission();

    I2C.requestFrom(DS3231_I2C_ADDRESS, DS3231_REG_NUM);

    byte registerValues[DS3231_REG_NUM];
    for (byte i=0; i< DS3231_REG_NUM; i++) {
        registerValues[i] = I2C.read();
    }
    for (byte i=0; i< DS3231_REG_NUM; i++) {
        Serial.print(registerContents[i]);
        Serial.print('\t');
        Serial.println(registerValues[i], HEX);
    }
}
#endif

byte DS3231::decToBcd(byte val) {
    return (val/10 << 4) | (val%10);
}
byte DS3231::bcdToDec(byte val) {
    return (((val & 0xF0) >> 4)*10) + (val & 0x0F);
}

void DS3231::getTime(TimeStruct *time) {
    I2C.begin();
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(0);
    I2C.endTransmission();

    I2C.requestFrom(DS3231_I2C_ADDRESS, 7);

    time->seconds     = bcdToDec(I2C.read() & 0x7f);
    time->minutes     = bcdToDec(I2C.read());
    time->hours       = bcdToDec(I2C.read() & 0x3f);
    time->dayOfWeek   = bcdToDec(I2C.read());
    time->dayOfMonth  = bcdToDec(I2C.read());
    time->month       = bcdToDec(I2C.read());
    time->year        = bcdToDec(I2C.read());
    I2C.end();
}

int DS3231::getFullTemp() {
    I2C.begin();
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(DS3231_REG_MSB_Temp);
    I2C.endTransmission();

    I2C.requestFrom(DS3231_I2C_ADDRESS, 2);
    int result = I2C.read() << 2;
    result |= I2C.read() >> 6;
    I2C.end();
    if (result & 0x200) {
        result |= 0xFE00;
    }
    return result;
}

short DS3231::getShortTemp() {
    I2C.begin();
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(DS3231_REG_MSB_Temp);
    I2C.endTransmission();

    I2C.requestFrom(DS3231_I2C_ADDRESS, 1);
    short result = (short)I2C.read();
    I2C.end();
    return result;
}

void DS3231::setTime(TimeStruct *time) {
    I2C.begin();
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(0);
    I2C.write(decToBcd(time->seconds));
    I2C.write(decToBcd(time->minutes));
    I2C.write(decToBcd(time->hours));
    I2C.write(decToBcd(time->dayOfWeek));
    I2C.write(decToBcd(time->dayOfMonth));
    I2C.write(decToBcd(time->month));
    I2C.write(decToBcd(time->year));
    I2C.endTransmission();
    I2C.end();
}

void DS3231::setControl(byte control, byte status) {
    I2C.begin();
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(DS3231_REG_Control);
    I2C.write(control);
    I2C.write(status);
    I2C.endTransmission();
    I2C.end();
}
byte DS3231::registerRead(byte address) {
    I2C.begin();
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(address);
    I2C.endTransmission();

    I2C.requestFrom(DS3231_I2C_ADDRESS, 1);
    byte result = I2C.read();
    I2C.end();
    return result;
}

void DS3231::registerWrite(byte address, byte value) {
    I2C.begin();
    I2C.beginTransmission(DS3231_I2C_ADDRESS);
    I2C.write(address);
    I2C.write(value);
    I2C.endTransmission();
    I2C.end();
}

#ifdef DS3231_DEBUG
static char *DS3231::registerContents[0x13] = {
    /* 0x00 */ "Seconds",
    /* 0x01 */ "Minutes",
    /* 0x02 */ "Hours",
    /* 0x03 */ "Day",
    /* 0x04 */ "Date",
    /* 0x05 */ "Month",
    /* 0x06 */ "Year",
    /* 0x07 */ "A1_Seconds",
    /* 0x08 */ "A1_Minutes",
    /* 0x09 */ "A1_Hours",
    /* 0x0A */ "A1_Date",
    /* 0x0B */ "A2_Minutes",
    /* 0x0C */ "A2_Hours",
    /* 0x0D */ "A2_Date",
    /* 0x0E */ "Control",
    /* 0x0F */ "Status",
    /* 0x10 */ "Offset",
    /* 0x11 */ "MSB_Temp",
    /* 0x12 */ "LSB_Temp"
};
#endif
