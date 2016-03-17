/* BLUETOOTH_BLUESMIRF.INO
   Bluetooth communication of Snowboard using Sparkfun BlueSMiRF
   This code is a modified version of Sparkfun code at
   https://github.com/sparkfun/BlueSMiRF
   Kitronyx Inc. (http://www.kitronyx.com)
   License: Public Domain
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
	Serial1.begin(115200); // the Bluetooth Mate defaults to 115200bps
	Serial1.print("$$$"); // enter command mode
	delay(100);  // short delay, wait for the Mate to send back CMD
	Serial1.println("U,9600,N"); // temporarily Change the baudrate to 9600, no parity
	// 115200 can be too fast at times for NewSoftSerial to relay the data reliably
	Serial1.begin(9600);  // start bluetooth serial at 9600
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
		int inByte = Serial1.read();

		snowforce.read(data);

		for (int i = 0; i < SNOWBOARD_DATA-1; i++)
		{
			Serial1.print(data[i]);
			Serial1.print(",");
		}
		Serial1.println(data[SNOWBOARD_DATA-1]);
		
		Serial.println("data sent to via bluetooth.");
	}
}

