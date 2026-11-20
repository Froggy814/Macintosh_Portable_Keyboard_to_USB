/*This code is meant for a Macintosh Portable keyboard or maybe Powerbook...
The microcontroller chosen is a ESP32-S3 because it has many analog pins. I could go with a pico but then I wouldn't have as much
analog to work with. It has every character that the Macintosh Portable keyboard has, and this took time. But not that long.
Hopefully... if the values are off in someway please!!!! let me know so I can fix it.*/

#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;


// Timer delay for each button so they dont go FIRIIRIJI{ESDHPIOUFdsjuio...}
#define PAUSE(ms) ([] { \
  static unsigned long t = 0; \
  if (millis() - t < (ms)) return false; \
  t = millis(); \
  return true; \
}())

// Struct to read value of y? and then whether x???? and then it does the <=> and the if statement works.

int readMedian(int pin) {
  int s[9];
  for (int i = 0; i < 9; i++) s[i] = analogRead(pin);
  for (int i = 1; i < 9; i++)  // insertion sort
    for (int j = i; j > 0 && s[j - 1] > s[j]; j--) {
      int t = s[j];
      s[j] = s[j - 1];
      s[j - 1] = t;
    }
  return s[4];  // middle value
}

struct R {
  int lo, hi;
};
bool operator==(int p, R r) {
  auto in = [&] {
    int v = readMedian(p);
    return v >= r.lo && v <= r.hi;
  };
return in() && (delay(4), in()) && (delay(4), in());
}

//delay how fast can you click?
int B = 140;

// Values of voltage divider 10k and ↓
R x0 = { 1180, 1260 };   // 22k ohm resistor
R x1 = { 1530, 1600 };   // 15k ohm resistor
R x2 = { 1920, 2020 };   // 10k ohm resistor
R x3 = { 2280, 2390 };   // 6.8k ohm resistor
R x4 = { 2620, 2770 };   // 4.7k ohm resistor
R x5 = { 2900, 3050 };   // 3.3k ohm resistor
R x6 = { 3260, 3350 };   // 2.2k ohm resistor
R x7 = { 3550, 3650 };   // 1.5k ohm resistor
R x8 = { 3790, 3860 };   // 1k ohm resistor
R x9 = { 3861, 4079 };   // 680 ohm resistor
R x10 = { 4080, 5000 };  // Zero ohm resistor

//ANALOGINPUTS 1-8
#define y0 3
#define y1 5
#define y2 6
#define y3 7
#define y4 15
#define y5 10
#define y6 17
#define y7 18

// DIGITALINPUTS
#define shift 9
#define caps 11
#define ctrl 12
#define cmd 14
#define optn 13

void setup() {
  // BEGIN
  Serial.begin(115200);
  Keyboard.begin();
  USB.begin();

  //PinMODES
  pinMode(y0, INPUT);
  pinMode(y1, INPUT);
  pinMode(y2, INPUT);
  pinMode(y3, INPUT);
  pinMode(y4, INPUT);
  pinMode(y5, INPUT);
  pinMode(y6, INPUT);
  pinMode(y7, INPUT);
  pinMode(shift, INPUT);
  pinMode(caps, INPUT);
  pinMode(ctrl, INPUT);
  pinMode(cmd, INPUT);
  pinMode(optn, INPUT);

  //Startup ifer
  delay(1000);
  if (0 == 1) {
    Serial.println("failure");
  } else {
    Serial.println("Keyboard Online!");
  }
}

void loop() {

  //Special Keys

  if (digitalRead(shift) == HIGH) {
    Keyboard.write(KEY_RIGHT_SHIFT);
    Keyboard.write(KEY_LEFT_SHIFT);
  }

  if (digitalRead(caps) == HIGH) {
    Keyboard.write(KEY_CAPS_LOCK);
  }

  if (digitalRead(ctrl) == HIGH) {
    Keyboard.write(KEY_RIGHT_CTRL);
    Keyboard.write(KEY_LEFT_CTRL);
  }

  if (digitalRead(cmd) == HIGH) {
    Keyboard.write(KEY_LEFT_GUI);
    Keyboard.write(KEY_RIGHT_GUI);
  }

  if (digitalRead(optn) == HIGH) {
    Keyboard.write(KEY_RIGHT_ALT);
    Keyboard.write(KEY_LEFT_ALT);
  }


Serial.print("y0 = ");
Serial.println(analogRead(y0));

Serial.print("y1 = ");
Serial.println(analogRead(y1));

Serial.print("y2 = ");
Serial.println(analogRead(y2));

Serial.print("y3 = ");
Serial.println(analogRead(y3));

Serial.print("y4 = ");
Serial.println(analogRead(y4));

Serial.print("y5 = ");
Serial.println(analogRead(y5));

Serial.print("y6 = ");
Serial.println(analogRead(y6));

Serial.print("y7 = ");
Serial.println(analogRead(y7));

Serial.print("Shift = ");
Serial.println(digitalRead(shift));

delay(2000);
}