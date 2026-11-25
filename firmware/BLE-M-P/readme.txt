Firmware designed and coded by: Froggy814 from 68kmla and Tinkerdifferent, (Disclaimer, AI was NOT used in this project. Not one lick of it)
Copyright info: Ask before you use, I either give consent or no. And read the license. (If I say no you cannot use it.)
Date: 11/24/2026
Rev: 1

How to use BLE-M-P: The first github repo for ESP32 ADB conversion to mice that connect through BLE!

First flash the ESP32 with the ino. You use Arduino IDE to flash. You also need to install ESP32 board library if you are using the ESP32-S3 DEV board like I did, but you can probably use a different board if you like.

Inside the external directory from where you got this file are the libraries that you need to copy/paste into your Arduino/libraries folder. On Windows that is usually in Documents. On Linux it is in Home. (I don't know about macs) Then it will compile.

If you do not have the pinout to the Macintosh Portable Pheripherals connector there is a photo in the hardware directory, that shows the pinout; to help you if needed.

Okay, you have finally flashed your ESP32, you need to hook up your Mac Portable Trackball which is quite simple hook the ADB pin to GPIO 36, and then you need to hook a +5v power source to the +5v pin and a GND pin on the connector (one from the power source and the other from the esp32 make sure you have a common ground for them all) And then you add a resistor (2.2k to 1k ohm) between the 3.3v pin and the ADB pin on the ESP32. Easy. Now that you have connected it go and have some fun! You may need to change the interval time to make it do diagnals but otherwise it should work perfectly. If you have any complaints please let me know! 🙂
