SNOWFOCE
========

General
-------
Snowforce Arduino firmware gets gets matrix data from the onboard force matrix controller and send it to a PC.

Writing your own firmware using force matrix sensing feature of Snowboard
-------

See the skeleton code below for your own projects.

```cpp
#include <Wire.h>
#include <Snowforce.h>

Snowforce snowforce;

void setup()
{
    Wire.begin(); // start communication with the onboard force controller
    snowforce.begin(); // start tactile sensing part of snowboard
    
    // TODO: put your codes here
}

void loop()
{
    // pressure mapping data
    // tactile sensing part always give maximum
    // number of data (10x16 = 160)
    byte data[160] = {0, }; 
    snowforce.read(data);

    // TODO: put your codes here
}
```