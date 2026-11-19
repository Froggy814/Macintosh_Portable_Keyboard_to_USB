/*This code is meant for a Macintosh Portable keyboard or maybe Powerbook...
The microcontroller chosen is a ESP32-S3 because it has many analog pins. I could go with a pico but then I wouldn't have as much
analog to work with. It has every character that the Macintosh Portable keyboard has, and this took time. But not that long.
Hopefully... if the values are off in someway please!!!! let me know so I can fix it.*/

#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#define runEvery(t) for (static typeof(t) _lasttime; \
                         (typeof(t))((typeof(t))millis() - _lasttime) > (t); \
                         _lasttime = millis())

// Struct to read value of y? and then whether x???? and then it does the <=> and the if statement works.

struct R {
  int min, max;
};
bool operator==(int p, R r) {

  int p3 = analogRead(p);
  if (p3 < r.min || p3 > r.max) return false;  // <-- ADD THIS ONE LINE (0ms skip!)
  unsigned long startMillis = millis();
  while (millis() - startMillis < 2) {}

  int p2 = analogRead(p);
  startMillis = millis();
  while (millis() - startMillis < 2) {}

  int p1 = analogRead(p);
  return ((r.min <= p3) && (p3 <= r.max)) && ((r.min <= p2 && p2 <= r.max)) && ((r.min <= p1 && p1 <= r.max));
}
//delay backspace?
int A = 135;
//delay how fast can you click?
int B = 160;

// Values of voltage divider 10k and ↓
R x0 = { 1180, 1260 };   // 22k ohm resistor
R x1 = { 1490, 1600 };   // 15k ohm resistor
R x2 = { 1920, 2020 };   // 10k ohm resistor
R x3 = { 2280, 2390 };   // 6.8k ohm resistor
R x4 = { 2620, 2770 };   // 4.7k ohm resistor
R x5 = { 2880, 3050 };   // 3.3k ohm resistor
R x6 = { 3260, 3350 };   // 2.2k ohm resistor
R x7 = { 3550, 3650 };   // 1.5k ohm resistor
R x8 = { 3790, 3860 };   // 1k ohm resistor
R x9 = { 3861, 4079 };   // 680 ohm resistor
R x10 = { 4080, 5000 };  // Zero ohm resistor

//ANALOGINPUTS 1-8
#define y0 3
#define y1 5
#define y2 8
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
    Keyboard.press(KEY_LEFT_SHIFT);
    Serial.println("SHIFT");
  } else {
    Keyboard.release(KEY_LEFT_SHIFT);
  }

  if (digitalRead(caps) == HIGH) {
    Keyboard.press(KEY_CAPS_LOCK);
    Serial.println("CAPSLOCK");
  } else {
    Keyboard.release(KEY_CAPS_LOCK);
  }

  if (digitalRead(ctrl) == HIGH) {
    Keyboard.press(KEY_LEFT_CTRL);
    Serial.println("CTRL");
  } else {
    Keyboard.release(KEY_LEFT_CTRL);
  }

  if (digitalRead(cmd) == HIGH) {
    Keyboard.press(KEY_LEFT_GUI);
    Serial.println("CMD");
  } else {
    Keyboard.release(KEY_LEFT_GUI);
  }

  if (digitalRead(optn) == HIGH) {
    Keyboard.press(KEY_LEFT_ALT);
    Serial.println("ALT");
  } else {
    Keyboard.release(KEY_LEFT_ALT);
  }

  // x0 defines
  if (y0 == x0) {
    runEvery(B) {
      Keyboard.write(KEY_KP_1);
      Serial.println("1");
    }
  }
  if (y1 == x0) {
    runEvery(B) {
      Keyboard.write(KEY_NUM_LOCK);
      Serial.println("NUMed");
    }
  }
  if (y2 == x0) {
    runEvery(B) {
      Keyboard.write(KEY_KP_3);
      Serial.println("3");
    }
  }
  if (y4 == x0) {
    runEvery(B) {
      Keyboard.write(KEY_TAB);
      Serial.println("TAB");
    }
  }
  if (y5 == x0) {
    runEvery(B) {
      Keyboard.write(KEY_LEFT_ARROW);
      Serial.println("LEFT");
    }
  }
  if (y6 == x0) {
    runEvery(B) {
      Keyboard.write('a');
      Serial.println("a");
    }
  }

  // x1 defines
  if (y1 == x1) {
    runEvery(B) {
      Keyboard.write(KEY_KP_2);
      Serial.println("2");
    }
  }
  if (y3 == x1) {
    runEvery(B) {
      Keyboard.write(KEY_KP_4);
      Serial.println("4");
    }
  }
  if (y4 == x1) {
    runEvery(B) {
      Keyboard.write('q');
      Serial.println("q");
    }
  }
  if (y6 == x1) {
    runEvery(B) {
      Keyboard.write('s');
      Serial.println("s");
    }
  }
  if (y7 == x1) {
    runEvery(B) {
      Keyboard.write('z');
      Serial.println("z");
    }
  }

  // x2 defines
  if (y0 == x2) {
    runEvery(B) {
      Keyboard.write(KEY_KP_ENTER);
      Serial.println("Enter");
    }
  }
  // if (y3 == x2) ?? 5 and +????
  if (y4 == x2) {
    runEvery(B) {
      Keyboard.write('w');
      Serial.write("w");
    }
  }
  if (y5 == x2) {
    runEvery(B) {
      Keyboard.write(KEY_UP_ARROW);
      Serial.println("UP");
    }
  }
  if (y6 == x2) {
    runEvery(B) {
      Keyboard.write(KEY_DOWN_ARROW);
      Serial.println("DOWN");
    }
  }
  if (y7 == x2) {
    runEvery(B) {
      Keyboard.write('x');
      Serial.println("x");
    }
  }

  // x3 defines
  if (y0 == x3) {
    runEvery(B) {
      Keyboard.write('=');
      Serial.println("=");
    }
  }
  if (y1 == x3) {
    runEvery(B) {
      Keyboard.write(KEY_KP_6);
      Serial.println("6");
    }
  }
  // if (y2/y6 == x3) prints / and * for numpad
  if (y3 == x3) {
    runEvery(B) {
      Keyboard.write(KEY_KP_MINUS);
      Serial.println("-");
    }
  }
  if (y4 == x3) {
    runEvery(B) {
      Keyboard.write('e');
      Serial.println("e");
    }
  }
  if (y5 == x3) {
    runEvery(B) {
      Keyboard.write('d');
      Serial.println("d");
    }
  }
  if (y7 == x3) {
    runEvery(B) {
      Keyboard.write('c');
      Serial.println("c");
    }
  }

  // x4 defines
  if (y0 == x4) {
    runEvery(B) {
      Keyboard.write(KEY_KP_0);
      Serial.println("0");
    }
  }
  if (y2 == x4) {
    runEvery(B) {
      Keyboard.write(KEY_KP_8);
      Serial.println("8");
    }
  }
  if (y4 == x4) {
    runEvery(B) {
      Keyboard.write('r');
      Serial.println("r");
    }
  }
  if (y5 == x4) {
    runEvery(B) {
      Keyboard.write(KEY_RIGHT_ARROW);
      Serial.println("RIGHT");
    }
  }
  if (y6 == x4) {
    runEvery(B) {
      Keyboard.write('f');
      Serial.println("f");
    }
  }
  if (y7 == x4) {
    runEvery(B) {
      Keyboard.write('v');
      Serial.println("v");
    }
  }

  // x5 defines
  if (y1 == x5) {
    runEvery(B) {
      Keyboard.write(KEY_KP_7);
      Serial.println("7");
    }
  }
  if (y2 == x5) {
    runEvery(B) {
      Keyboard.write(KEY_KP_DOT);
      Serial.println(".");
    }
  }
  if (y3 == x5) {
    runEvery(B) {
      Keyboard.write(KEY_KP_9);
      Serial.println("9");
    }
  }
  if (y4 == x5) {
    runEvery(B) {
      Keyboard.write(KEY_KP_ENTER);
      Serial.println("Enter");
    }
  }
  if (y5 == x5) {
    runEvery(B) {
      Keyboard.write('u');
      Serial.println("u");
    }
  }
  if (y6 == x5) {
    runEvery(B) {
      Keyboard.write('b');
      Serial.println("b");
    }
  }
  if (y7 == x5) {
    runEvery(B) {
      Keyboard.write(' ');
      Serial.println("SPACE");
    }
  }

  // x6 defines
  if (y0 == x6) {
    runEvery(B) {
      Keyboard.write(KEY_ESC);
      Serial.println("esc");
    }
  }
  if (y1 == x6) {
    runEvery(B) {
      Keyboard.write('1');
      Serial.println("1");
    }
  }
  if (y2 == x6) {
    runEvery(B) {
      Keyboard.write('2');
      Serial.println("2");
    }
  }
  if (y3 == x6) {
    runEvery(B) {
      Keyboard.write('3');
      Serial.println("3");
    }
  }
  if (y4 == x6) {
    runEvery(B) {
      Keyboard.write('i');
      Serial.println("i");
    }
  }
  if (y5 == x6) {
    runEvery(A) {
      Keyboard.write(KEY_BACKSPACE);
      Serial.println("BACKSPACE");
    }
  }
  if (y6 == x6) {
    runEvery(B) {
      Keyboard.write('h');
      Serial.println("h");
    }
  }

  // x7 Defines
  if (y0 == x7) {
    runEvery(B) {
      Keyboard.write('4');
      Serial.println("4");
    }
  }
  if (y1 == x7) {
    runEvery(B) {
      Keyboard.write('`');
      Serial.println("`");
    }
  }
  if (y2 == x7) {
    runEvery(B) {
      Keyboard.write('g');
      Serial.println("g");
    }
  }

  if (y3 == x7) {
    runEvery(B) {
      Keyboard.write('\\');
      Serial.println("\\");
    }
  }
  if (y4 == x7) {
    runEvery(B) {
      Keyboard.write('k');
      Serial.println("k");
    }
  }
  if (y5 == x7) {
    runEvery(B) {
      Keyboard.write('l');
      Serial.println("l");
    }
  }
  if (y6 == x7) {
    runEvery(B) {
      Keyboard.write('j');
      Serial.println("j");
    }
  }
  if (y7 == x7) {
    runEvery(B) {
      Keyboard.write('n');
      Serial.println("n");
    }
  }

  // x8 Defines
  if (y0 == x8) {
    runEvery(B) {
      Keyboard.write('5');
      Serial.println("5");
    }
  }
  if (y1 == x8) {
    runEvery(B) {
      Keyboard.write('t');
      Serial.println("t");
    }
  }
  if (y2 == x8) {
    runEvery(B) {
      Keyboard.write('y');
      Serial.println("y");
    }
  }
  if (y3 == x8) {
    runEvery(B) {
      Keyboard.write('[');
      Serial.println("[");
    }
  }
  if (y4 == x8) {
    runEvery(B) {
      Keyboard.write('p');
      Serial.println("p");
    }
  }
  if (y5 == x8) {
    runEvery(B) {
      Keyboard.write(';');
      Serial.println(';');
    }
  }
  if (y6 == x8) {
    runEvery(B) {
      Keyboard.write(',');
      Serial.println(",");
    }
  }
  if (y7 == x8) {
    runEvery(B) {
      Keyboard.write('m');
      Serial.println("m");
    }
  }

  // x9 define
  if (y0 == x9) {
    runEvery(B) {
      Keyboard.write('6');
      Serial.println("6");
    }
  }
  if (y1 == x9) {
    runEvery(B) {
      Keyboard.write('7');
      Serial.println("7");
    }
  }
  if (y2 == x9) {
    runEvery(B) {
      Keyboard.write('8');
      Serial.println("8");
    }
  }
  if (y3 == x9) {
    runEvery(B) {
      Keyboard.write('9');
      Serial.println("9");
    }
  }
  if (y4 == x9) {
    runEvery(B) {
      Keyboard.write(']');
      Serial.println("]");
    }
  }
  if (y5 == x9) {
    runEvery(B) {
      Keyboard.write('\'');
      Serial.println("\'");
    }
  }
  if (y6 == x9) {
    runEvery(B) {
      Keyboard.write('/');
      Serial.println("/");
    }
  }

  // x10 defines
  if (y0 == x10) {
    runEvery(B) {
      Keyboard.write('=');
      Serial.println("=");
    }
  }
  if (y1 == x10) {
    runEvery(B) {
      Keyboard.write('-');
      Serial.println("-");
    }
  }
  if (y2 == x10) {
    runEvery(B) {
      Keyboard.write('0');
      Serial.println("0");
    }
  }
  if (y3 == x10) {
    runEvery(B) {
      Keyboard.write('o');
      Serial.println("o");
    }
  }
  if (y5 == x10) {
    runEvery(B) {
      Keyboard.write(KEY_RETURN);
      Serial.println("RETURN");
    }
  }
  if (y6 == x10) {
    runEvery(B) {
      Keyboard.write('.');
      Serial.println(".");
    }
  }
}