/*
 forcespeed.ino
 calculate speed to readout force data.

 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#include <Wire.h>
#include <Snowforce.h>

Snowforce snowforce;

#define NUM_NODE 160
#define NUM_READ 100
unsigned long tic;
unsigned long toc;
byte data[NUM_NODE] = {0, };
float frame_ts; // ms
float frame_fs; // Hz
float node_fs; // ms
float node_ts_khz; // KHz

void setup()
{
  Wire.begin();   // start i2c communication
  Serial.begin(115200);  // start serial for output
  snowforce.begin(); // start tactile sensing part of snowboard
}

void loop()
{
  tic = millis();
  for (int i = 0; i < NUM_READ; i++)
  {
    snowforce.read(data);
  }
  toc = millis();

  frame_ts = (float)(toc - tic) / (float)NUM_READ; // ms
  frame_fs = 1.0f / (frame_ts); // KHz
  frame_fs = frame_fs * 1000.0f; // Hz

  node_ts_khz = frame_ts / (float)NUM_NODE; // ms
  node_fs = 1.0f / node_ts_khz; // Khz

  Serial.print("Read 100 frame samples (160 force nodes per sample) per ");
  Serial.print(toc - tic);
  Serial.println(" (ms).");
  Serial.print("* ADC reading speed for a single frame is ");
  Serial.print(frame_ts);
  Serial.print("(ms) (");
  Serial.print(frame_fs);
  Serial.println(" Hz).");
  Serial.print("* ADC reading speed for a single node is ");
  Serial.print(node_ts_khz);
  Serial.print(" (ms) (");
  Serial.print(node_fs);
  Serial.println(" KHz).");
}
