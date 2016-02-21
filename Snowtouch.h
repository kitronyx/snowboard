/*
 Snowtouch.h
 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#ifndef _SNOWTOUCH_H_
#define _SNOWTOUCH_H_

#include "Arduino.h"
#include <Wire.h>
// MPR121 headr writen by DFRobot is included.
#include "mpr121.h"

// I2C address of MPR121
#define MPR121_ADDRESS 0x5A

class Snowtouch
{
private:
    uint16_t sensor[12];
    
private:
    void mpr121_setup(void);
    void set_register(int address, unsigned char r, unsigned char v);
    
public:
    void begin(void);
    void read(void);
    uint16_t getTouch(int i);
};

#endif // _SNOWTOUCH_H_