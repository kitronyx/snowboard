/*
 Snowforce.ino
 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
 
 Analog electrode reading from Touch Shield

 This code is based on the code at
 http://bildr.org/2011/05/mpr121_arduino/
 and modified by Wook Chang (wook.chang@kitronyx.com)
*/

#include <Wire.h>
#include <Snowtouch.h>

Snowtouch snowtouch;
int inByte = 0; // incoming serial byte

void setup()
{   
    // start serial port at 9600 bps and wait for port to open:
    Serial.begin(115200);
    Wire.begin();
    snowtouch.begin();
    
//    while (!Serial) {
//        ; // wait for serial port to connect. Needed for Leonardo only
//    }
//
//    establishContact(); // send a byte to establish contact until receiver responds
}

void loop()
{
    // if we get a valid byte, send out sensor data to a host PC.
    if (Serial.available() > 0)
    {   
        // get incoming byte:
        inByte = Serial.read();
        
        snowtouch.read();
        
        // send sensor values:
        for (int i = 0; i < 11; i++)
        {
            Serial.print(snowtouch.getTouch(i));
            Serial.print(",");
        }
        Serial.println(snowtouch.getTouch(11));
    }
}

void establishContact() {
    while (Serial.available() <= 0) {
        Serial.println("send any character to arduino.");   // send an initial string
        delay(300);
    }
}
