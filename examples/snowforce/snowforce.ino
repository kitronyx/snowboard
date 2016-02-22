/*
 Snowforce.ino
 Copyright (c) 2014-2016 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#include <Wire.h>
#include <Snowforce.h>

Snowforce snowforce;

void setup()
{
    Wire.begin();   // start i2c communication
    Serial.begin(115200);  // start serial for output
    snowforce.begin(); // start tactile sensing part of snowboard
}

void loop()
{
    // pressure mapping data
    // tactile sensing part always give maximum
    // number of data (10x16 = 160)
    byte data[160] = {0, }; 

    // send data only pc wants it
    if (Serial.available() > 0)
    {
        int inByte = Serial.read();
        
        snowforce.read(data);

        for (int i = 0; i < 159; i++)
        {
            Serial.print(data[i]);
            Serial.print(",");
        }
        Serial.println(data[159]);
    }
}
