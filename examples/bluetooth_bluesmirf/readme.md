Snowboard Bluetooth Example
===========================

General
-------
This example shows how to use Sparkfun's [BlueSMiRF] (https://github.com/sparkfun/BlueSMiRF) with Snowboard.

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

Note for Korean Users
---------------------
You can buy a compatible bluetooth module at:
* http://www.funnykit.co.kr/shop/goods/goods_view.php?goodsno=20238&inflow=naver&NaPm=ct%3Dilui6mb4%7Cci%3D486608b309e4df5bcf75e110db414d5ad500dd93%7Ctr%3Dsls%7Csn%3D263904%7Chk%3D09869d46f1352f29b185e8bc6b069f363fc2c728
