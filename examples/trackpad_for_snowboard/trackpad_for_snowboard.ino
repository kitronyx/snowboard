/*
 trackpad_for_snowboard.ino
 Single touch trackpad example for Snowboard.
 This example requires:
 * Snowboard http://www.kitronyx.com/snowboard.html
 * Capacitive trackpad for Snowboard http://www.kitronyx.com/store/p7/Capacitive_Trackpad_for_Snowboard.html
 Copyright (c) 2014 Kitronyx http://www.kitronyx.com
 GPL V3.0
*/

#include <Wire.h>
#include <Snowtouch.h>

Snowtouch snowtouch;

#define NROW 5
#define NCOL 7
#define TOUCH_RESOLUTION 4096

long baseline[12] = {0, };
long reading[12] = {0, };
int threshold = 10;

int touchid = 0;
int pen = 1;
int touchx;
int touchy;

void setup()
{
  int i, j;
  Serial.begin(115200);
  Wire.begin();
  snowtouch.begin();

  // wait till MPR121 is stabilized.
  delay(100);

  // scan base line
  int nsum = 5;
  for (i = 0; i < nsum; i++)
  {
    snowtouch.read();
    for (j = 0; j < 12; j++)
    {
      baseline[j] += snowtouch.getTouch(j);
    }
  }

  for (i = 0; i < 12; i++)
  {
    baseline[i] = baseline[i] / 5;
    Serial.println(baseline[i]);
  }
}

void loop()
{
  int i, j;
  long numx = 0;
  long denx = 0;
  long numy = 0;
  long deny = 0;
  bool touched = false;

  snowtouch.read();

  // get touch data (touched signal is large)
  for (i = 0; i < 12; i++)
  {
    reading[i] = baseline[i] - snowtouch.getTouch(i);
    if (reading[i] < 0) reading[i] = 0;
  }

  // check touch
  for (i = 0; i < 12; i++)
  {
    if (reading[i] > threshold)
    {
      touched = true;
      break;
    }
  }

  if (touched == true)
  {
    // compute x and y position.
    for (i = 0; i < NROW; i++)
    {
      for (j = 0; j < NCOL; j++)
      {
        numx += reading[5 + j] * j;
        denx += reading[5 + j];
        numy += reading[4 - i] * i;
        deny += reading[4 - i];
      }
    }

    numx *= TOUCH_RESOLUTION;
    denx *= NCOL - 1;

    numy *= TOUCH_RESOLUTION;
    deny *= NROW - 1;

    touchx = numx / denx;
    touchy = numy / deny;

    // output touch data to be used touchplot.pde
    // http://sites.kitronyx.com/wiki/snowpad/examples/readsnowpad-code-to-read-multi-touch-data#TOC-Visualization
    Serial.print(touchid);
    Serial.print(",");
    Serial.print(pen);
    Serial.print(",");
    Serial.print(touchx);
    Serial.print(",");
    Serial.println(touchy);
  }
  else
  {
    Serial.print(0);
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    Serial.print(0);
    Serial.print(",");
    Serial.println(0);
  }

}
