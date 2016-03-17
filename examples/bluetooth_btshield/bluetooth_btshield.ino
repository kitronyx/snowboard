/*  BLUETOOTH_BTSHIELD.INO
	Bluetooth communication of Snowboard using SeeedStudio Bluetooth Shield.
	http://www.seeedstudio.com/depot/Bluetooth-Shield-V2-p-2416.html?cPath=19_21
	Copyright (c) Kitronyx Inc. 2014-2016
	http://www.kitronyx.com
	License GPL 3.0
	Date: 2016-03-17

	[Hardware connection]
	Snowboard D0 (RX) <--> BT TX
	Snowboard D1 (TX) <--> BT RX
	Snowboard USB <--> PC

	Force data will be transferred via BT moduel.
	Snowboard USB serial is in charge of reporting debug information.
*/

#include <Wire.h> // to communicate with force controller on snowboard
#include <Snowforce.h> // to use snowboard library

#define SNOWBOARD_DATA 160
Snowforce snowforce;

// Serial is responsible for communicating with PC.
// Serial1 is responsible for communicating with BT module.
void setup()
{
	Serial.begin(9600);  // begin the serial monitor at 9600bps

	Serial.println("Setup BT communication.");
	Serial1.begin(9600); // default bt baudrate is 9600bps
	delay(100); // short delay
	Serial.println("Finish to setup BT communication.");

	// start snowboard
	Serial.println("Setup force sensing.");
	Wire.begin(); // begin communication
	snowforce.begin(); // begin sensor reading
	Serial.println("Finished to setup force sensing.");
}

void loop()
{
	byte data[SNOWBOARD_DATA] = { 0, };
	// send data only host sends a request byte.
	// force data format is csv.
	// note your bluetooth host must send an arbitrary single byte to get data.
	if (Serial1.available() > 0)
	{
		int inByte = Serial1.read(); // empty buffer.

		snowforce.read(data);

		for (int i = 0; i < SNOWBOARD_DATA - 1; i++)
		{
			Serial1.print(data[i]);
			Serial1.print(",");
		}
		Serial1.println(data[SNOWBOARD_DATA - 1]);

		Serial.println("data sent to via bluetooth.");
	}
}
