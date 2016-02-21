/*
 Snowtouch.cpp
 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#include "Snowtouch.h"

void Snowtouch::begin(void)
{
    // to give mpr121 time to stabilize
    // before i2c communication.
    delay(100);
    for (int i = 0; i < 12; i++) sensor[i] = 0;
    mpr121_setup();
}

// Read data from four electrodes and print them.
void Snowtouch::read(void)
{
//    Wire.requestFrom(MPR121_ADDRESS,12); 
    Wire.requestFrom(MPR121_ADDRESS,28); 
    
    byte LSB = Wire.read();
    byte MSB = Wire.read();
    byte OOR1 = Wire.read();
    byte OOR2 = Wire.read();
    byte ELE0_LSB = Wire.read();
    byte ELE0_MSB = Wire.read();
    byte ELE1_LSB = Wire.read();
    byte ELE1_MSB = Wire.read();
    byte ELE2_LSB = Wire.read();
    byte ELE2_MSB = Wire.read();
    byte ELE3_LSB = Wire.read();
    byte ELE3_MSB = Wire.read();
    byte ELE4_LSB = Wire.read();
    byte ELE4_MSB = Wire.read();
    byte ELE5_LSB = Wire.read();
    byte ELE5_MSB = Wire.read();
    byte ELE6_LSB = Wire.read();
    byte ELE6_MSB = Wire.read();
    byte ELE7_LSB = Wire.read();
    byte ELE7_MSB = Wire.read();
    byte ELE8_LSB = Wire.read();
    byte ELE8_MSB = Wire.read();
    byte ELE9_LSB = Wire.read();
    byte ELE9_MSB = Wire.read();
    byte ELE10_LSB = Wire.read();
    byte ELE10_MSB = Wire.read();
    byte ELE11_LSB = Wire.read();
    byte ELE11_MSB = Wire.read();

    
    sensor[0] = ((ELE0_MSB << 8) | ELE0_LSB);
    sensor[1] = ((ELE1_MSB << 8) | ELE1_LSB);
    sensor[2] = ((ELE2_MSB << 8) | ELE2_LSB);
    sensor[3] = ((ELE3_MSB << 8) | ELE3_LSB);
    
    sensor[4] = ((ELE4_MSB << 8) | ELE4_LSB);
    sensor[5] = ((ELE5_MSB << 8) | ELE5_LSB);
    sensor[6] = ((ELE6_MSB << 8) | ELE6_LSB);
    sensor[7] = ((ELE7_MSB << 8) | ELE7_LSB);
    
    sensor[8] = ((ELE8_MSB << 8) | ELE8_LSB);
    sensor[9] = ((ELE9_MSB << 8) | ELE9_LSB);
    sensor[10] = ((ELE10_MSB << 8) | ELE10_LSB);
    sensor[11] = ((ELE11_MSB << 8) | ELE11_LSB);
}

uint16_t Snowtouch::getTouch(int i)
{
    return sensor[i];
}


void Snowtouch::mpr121_setup(void)
{

    //digitalWrite(3, LOW);
  set_register(MPR121_ADDRESS, ELE_CFG, 0x00); 
  
  // Section A - Controls filtering when data is > baseline.
  set_register(MPR121_ADDRESS, MHD_R, 0x01);
  set_register(MPR121_ADDRESS, NHD_R, 0x01);
  set_register(MPR121_ADDRESS, NCL_R, 0x00);
  set_register(MPR121_ADDRESS, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(MPR121_ADDRESS, MHD_F, 0x01);
  set_register(MPR121_ADDRESS, NHD_F, 0x01);
  set_register(MPR121_ADDRESS, NCL_F, 0xFF);
  set_register(MPR121_ADDRESS, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(MPR121_ADDRESS, ELE0_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE0_R, REL_THRESH);
 
  set_register(MPR121_ADDRESS, ELE1_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE1_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE2_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE2_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE3_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE3_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE4_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE4_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE5_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE5_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE6_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE6_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE7_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE7_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE8_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE8_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE9_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE9_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE10_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE10_R, REL_THRESH);
  
  set_register(MPR121_ADDRESS, ELE11_T, TOU_THRESH);
  set_register(MPR121_ADDRESS, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(MPR121_ADDRESS, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(MPR121_ADDRESS, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(MPR121_ADDRESS, ATO_CFG0, 0x0B);
  set_register(MPR121_ADDRESS, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(MPR121_ADDRESS, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(MPR121_ADDRESS, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(MPR121_ADDRESS, ELE_CFG, 0x0C);
  
  //digitalWrite(3, HIGH);
}


void Snowtouch::set_register(int address, unsigned char r, unsigned char v)
{
    Wire.beginTransmission(address);
    Wire.write(r);
    Wire.write(v);
    Wire.endTransmission();
}
