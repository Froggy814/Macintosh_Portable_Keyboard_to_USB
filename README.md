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


# V0.0.2

This is improved upon the older one by a single day! well... Less then a day, but we don't talk semantics!

I fixed the code so it alt works, and the keyboard is just better comparitively because I used a different library for the ~MATRIX~ So it is a little better.

The wiring is almost identical but gpio 46 was having trouble so I had to move it to the next available gpio, which was gpio 37... So the wiring is now:


x0 - x10 goes to these GPIO's: 4, 5, 6, 7, 15, 16, 17, 18, 8, 3, 37, x0 starts at the left side and x10 is at the right. Easy!

y0 - y7 go to these ones: 9, 10, 11, 12, 13, 14, 1, 2, again y0 is at the left, and y7 is the right.

The Special keys are hooked in this order:
capslock 42,
shift 41,
ctrl 40,
optn 39,
cmd 38.


See, not much change, but now we need to talk upload. You upload using Arduino IDE, but you need a different library. You need, https://github.com/Nullkraft/Keypad this library and you need to change 2 values in keypad.h, or alternatively you can just replace it with the one I have supplied. All you need to do is change those 2 lines to what they are so that it will see, oh there are 11 rows, not a max of 10 so that it doesn't freak out and not work.


#define LIST_MAX 12		// Max number of keys on the active list.
#define MAPSIZE 11		// MAPSIZE is the number of rows (times 16 columns)

So, I think that covers it all. And it seems to be working muuuch better with the different library. 🙂
