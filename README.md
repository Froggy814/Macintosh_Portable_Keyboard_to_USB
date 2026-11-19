# Macintosh_Portable_Keyboard_to_USB

This is some code to make your Macintosh Portable's keyboard a new home.
I started this as a little side quest, I think it will be bigger then that...

I used a ESP32-S3 Dev board. You can probably change the library for a PICO or Arduino.
Wiring is simple and all, I just hope you have 24 GPIO's to tap into! :P

x0 - x10 goes to these GPIO's: 4, 5, 6, 7, 15, 16, 17, 18, 8, 3, 46, x0 starts at the left side and x10 is at the right. Easy!

y0 - y7 go to these ones: 9, 10, 11, 12, 13, 14, 1, 2, again y0 is at the left, and y7 is the right.

The Special keys are hooked in this order:
capslock 42,
shift 41,
ctrl 40,
optn 39,
cmd 38.

After you have it all hooked up, then you can flash the firmware. There are two firmwares but I will only explain the one that is good.

USB-K-P.ino is the one we shall focus on, all you need to do is hook up your ESP32-S3 dev board flash it, then switch USB ports and then wham! It should just work. You do have to put the library that I fixed into the arduino librarys folder. But it's simple you should be able to figure it out.

After you have flashed all of the stuff should work, you should be able to type on it as easily as ever. Of course you can't have a repo without an additive list. soooo here goes:

1. Bluetooth connection
2. Second ESP32 for ADB or other...
3. Case
4. Custom PCB with lights for spcl keys
5. confirmation of numpad
