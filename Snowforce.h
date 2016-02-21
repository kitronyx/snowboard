/*
 Snowforce.h
 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#ifndef _SNOWFORCE_H_
#define _SNOWFORCE_H_

#include "Arduino.h"
#include <Wire.h>

class Snowforce
{
private:
    byte data[180];
public:
    void begin(void);
    void read(byte * force);
};

#endif // _SNOWFORCE_H_
