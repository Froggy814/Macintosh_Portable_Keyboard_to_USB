Firmware designed and coded by: Froggy814 on 68kmla and Tinkerdifferent, (Disclaimer, AI was NOT used in this project. Not one lick of it)
Copyright info: Ask before you use, I either give consent or no. And read the license. (If I say no you cannot use it.)
Date: 11/18/2026
Rev: 2

How to install USB-K-P V0.0.1

First flash the ESP32 with the ino. You use Arduino IDE to flash. You also need to install ESP32 board library if you are using the ESP32-S3 DEV board like I did, but you can probably use a different board if you like.

Inside the external directory from where you got this file is the library that you need to copy/paste into your Arduino/libraries folder. On Windows that is usually in Documents. On Linux it is in Home. (I don't know about macs)

If you do not have the pinout to the Macintosh Portable Keyboard there is the photo in the hardware directory to help you if needed.

Now that you have flashed the firmware grab your Macintosh Portable Keyboard and wire it up. Here is how to wire it (on the left is the pin definition, and on the right is the GPIO on the ESP32 I have the firmware set to):

x0 - 4,
x1 - 5,
x2 - 6,
x3 - 7,
x4 - 15,
x5 - 16,
x6 - 17,
x7 - 18,
x8 - 8,
x9 - 3,
x10 - 37

and the y's,

y0 - 9,
y1 - 10,
y2 - 11,
y3 - 12,
y4 - 13,
y5 - 14,
y6 - 1,
y7 - 2,

and lastly the special keys,

Command - 38,
Control - 40,
Shift - 41,
Option - 39,
Caps Lock - 42,

And you have finished wiring!

Now, if you have flashed the firmware and the wiring is done, you need to move the USB cable to the other USB connector on the DEV board (if you are using the ESP32 DEV board), and then it should type! Happy typing! 🙂
