/*
 Snowfsr.ino
 Read and display outputs of single zone FSR attached to the Snowboard
 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#include <Wire.h>
#include <Snowforce.h>

Snowforce snowforce;

#define MAXFSR 10

void setup()
{
    Wire.begin();   // start i2c communication with Snowboard core or Snowboard 2
    Serial.begin(115200);  // start serial for output
    snowforce.begin(); // start tactile sensing part of Snowboard core or Snowboard 2
}

void loop()
{
    byte fsr_reading[MAXFSR];
    
    readSinglezoneFSR(fsr_reading);
    Serial.println(fsr_reading[0]);
    
    
//    for (int i = 0; i < MAXFSR; i++)
//    {
//        if (fsr_reading[i] > 0)
//        {
//            printFSR(i, fsr_reading[i]);
//        }
//    }
}

// read AD value of nth single zone FSR
void readSinglezoneFSR(byte * measurement)
{
    const int nsense = 10; // number columns of force matrix data
    byte data[160] = {0, };  // force matrix data

    snowforce.read(data);

    measurement[0] = data[140];

//    for (int i = 0; i < MAXFSR; i++)
//    {
//        measurement[i] = data[i * nsense + i];
//    }
}

// print AD value x of nth single FSR 
void printFSR(int n, byte x)
{
    Serial.print("FSR ");
    Serial.print(n);
    Serial.print(" at (D");
    Serial.print(n);
    Serial.print(", S");
    Serial.print(n);
    Serial.print(") gives AD value ");
    Serial.println(x);
}
