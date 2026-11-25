Firmware designed and coded by: Froggy814 from 68kmla and Tinkerdifferent, (Disclaimer, AI was NOT used in this project. Not one lick of it)
Copyright info: Ask before you use, I either give consent or no. And read the license. (If I say no you cannot use it.)
Date: 11/20/2026
Rev: 1

How to use USB-M-P

First flash the ESP32 with the ino. You use Arduino IDE to flash. You also need to install ESP32 board library if you are using the ESP32-S3 DEV board like I did, but you can probably use a different board if you like.

If you do not have the pinout to the Macintosh Portable Pheripherals connector there is a photo in the hardware directory, that shows the pinout; to help you if needed.

Now all you have to do is wire the Trackball up! Add a 1k-2.2k ohm resistor between the GPIO 36 (or your ADB input pin) and 3.3v on the ESP32, Then hook the Trackball up to the ESP32, just put the ADB pin to GPIO 36. And then supply +5v to the Trackball, just make  sure that they share a common GND. Thne have fun with your USB to ADB mouse adapter! YAY!
