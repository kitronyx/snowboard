Snowboard Bluetooth Example for SeeedStudio Bluetooth Shield 2.0
================================================================

General
-------
This example shows how to use SeeedStduio's [Bluetooth Shield 2.0] (http://www.seeedstudio.com/depot/Bluetooth-Shield-V2-p-2416.html) with Snowboard.

This code is written in Microsoft Visual Studio with Visual Micro Addon.
Main code is `bluetooth_bluesmirf.ino` and you can use conventional Arduino IDE to compile and upload it.

Hardware Configuration
----------------------
Connect BT module and Snowboard by consulting following pin map
* Connect Snowboard D0 (RX) to BT's TX
* Connect Snowboard D1 (TX) to BT's RX

Connect Snowboard to your PC. This connection is only for debugging.

Actual force data will be reported via BT module.

For more information about Snowboard serial configuration, visit following links:
* https://www.arduino.cc/en/Reference/Serial
* https://www.arduino.cc/en/Main/ArduinoBoardLeonardo

Bluetooth Shiel Document
------------------------
* http://www.seeedstudio.com/wiki/Bluetooth_Shield_V2.0
