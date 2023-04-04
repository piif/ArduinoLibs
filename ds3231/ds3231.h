#ifndef DS3231_H
#define DS3231_H

#include <Arduino.h>
#include "timeFunctions.h"

#define DS3231_I2C_ADDRESS 0x68
#define DS3231_REG_NUM  0x13

#define DS3231_REG_Seconds    0x00 // 0-59
#define DS3231_REG_Minutes    0x01 // 0-59
#define DS3231_REG_Hours      0x02 // bit 6 = AM/!PM
#define DS3231_REG_Day        0x03 // 1-7
#define DS3231_REG_Date       0x04 // 1-31
#define DS3231_REG_Month      0x05 // 1-12 , bit 7 = century
#define DS3231_REG_Year       0x06 // 0-99
#define DS3231_REG_A1_Seconds 0x07 
#define DS3231_REG_A1_Minutes 0x08 
#define DS3231_REG_A1_Hours   0x09 
#define DS3231_REG_A1_Date    0x0A 
#define DS3231_REG_A2_Minutes 0x0B 
#define DS3231_REG_A2_Hours   0x0C 
#define DS3231_REG_A2_Date    0x0D 
#define DS3231_REG_Control    0x0E 
#define DS3231_REG_Status     0x0F 
#define DS3231_REG_Offset     0x10 
#define DS3231_REG_MSB_Temp   0x11 
#define DS3231_REG_LSB_Temp   0x12 
class DS3231 {
public:
    typedef struct _ControlRegister {
        byte EOSC:1;  /* 0 */
        byte BBSQW:1; /* 0 */
        byte CONV:1;  /* 0 */
        byte RS2:1;   /* 1 */
        byte RS1:1;   /* 1 */
        byte INTCN:1; /* 1 */
        byte A2IE:1;  /* 0 */
        byte A1IE:1;  /* 0 */
    } ControlRegister;

    typedef struct _StatusRegister {
        byte OSF:1;    /* 1 */
        byte _fill:3;
        byte EN32kHz:1;/* 1 */
        byte BSY:1;    /* 0 */
        byte A2F:1;    /* 0 */
        byte A1F:1;    /* 0 */
    } StatusRegister;

    DS3231();

    byte decToBcd(byte val);
    byte bcdToDec(byte val);

    void getTime(TimeStruct *time);

    int getFullTemp();

    short getShortTemp();

    void setTime(TimeStruct *time);

    byte registerRead(byte address);
    void registerWrite(byte address, byte value);
    void setControl(byte control, byte status);

#ifdef DS3231_DEBUG
    void dumpAllRegisters();
#endif

private:
#ifdef DS3231_DEBUG
    static char *DS3231::registerContents[0x13];
#endif

};

#endif