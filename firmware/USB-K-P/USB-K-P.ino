#include <Keypad.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#define capslock 42
#define shift 41
#define ctrl 40
#define optn 39
#define cmd 38


bool capslock1 = HIGH;
bool shift1 = HIGH;
bool ctrl1 = HIGH;
bool optn1 = HIGH;
bool cmd1 = HIGH;


const byte ROWS = 11;  //four rows
const byte COLS = 8;   //four columns
byte rowPins[ROWS] = { 4, 5, 6, 7, 15, 16, 17, 18, 8, 3, 37 };
byte colPins[COLS] = { 9, 10, 11, 12, 13, 14, 1, 2 };
char hexaKeys[ROWS][COLS] = {
  /* X0  */ { KEY_KP_1, KEY_NUM_LOCK, KEY_KP_3, 0, KEY_TAB, KEY_LEFT_ARROW, 'a', 0 },
  /* X1  */ { 0, KEY_KP_2, 0, KEY_KP_4, 'q', 0, 's', 'z' },
  /* X2  */ { KEY_KP_ENTER, 0, 0, 0, 'w', KEY_UP_ARROW, KEY_DOWN_ARROW, 'x' },
  /* X3  */ { '=', KEY_KP_6, 0, KEY_KP_MINUS, 'e', 'd', 0, 'c' },
  /* X4  */ { KEY_KP_0, 0, KEY_KP_8, 0, 'r', KEY_RIGHT_ARROW, 'f', 'v' },
  /* X5  */ { 0, KEY_KP_7, KEY_KP_DOT, KEY_KP_9, KEY_KP_ENTER, 'u', 'b', ' ' },
  /* X6  */ { KEY_ESC, '1', '2', '3', 'i', KEY_BACKSPACE, 'h', 0 },
  /* X7  */ { '4', '`', 'g', '\\', 'k', 'l', 'j', 'n' },
  /* X8  */ { '5', 't', 'y', '[', 'p', ';', ',', 'm' },
  /* X9  */ { '6', '7', '8', '9', ']', '\'', '/', 0 },
  /* X10 */ { '=', '-', '0', 'o', 0, KEY_RETURN, '.', 0 }
};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  customKeypad.addStatedEventListener(keypadEvent);
  customKeypad.setDebounceTime(2);
  customKeypad.setHoldTime(500);
  Keyboard.begin();
  USB.begin();

  pinMode(ctrl, INPUT_PULLUP);
  pinMode(shift, INPUT_PULLUP);
  pinMode(cmd, INPUT_PULLUP);
  pinMode(optn, INPUT_PULLUP);
  pinMode(capslock, INPUT_PULLUP);
}

void loop() {
  customKeypad.getKeys();
  specialKeys();
}



void specialKeys() {

  if (digitalRead(ctrl) == LOW && ctrl1 == HIGH) {
    Keyboard.press(KEY_LEFT_CTRL);
    Serial.println("CTRL");
    ctrl1 = LOW;
  } else if (digitalRead(ctrl) == HIGH && ctrl1 == LOW) {
    Keyboard.release(KEY_LEFT_CTRL);
    ctrl1 = HIGH;
  }
  if (digitalRead(cmd) == LOW && cmd1 == HIGH) {
    Keyboard.press(KEY_LEFT_GUI);
    Serial.println("CMD");
    cmd1 = LOW;
  } else if (digitalRead(cmd) == HIGH && cmd1 == LOW) {
    Keyboard.release(KEY_LEFT_GUI);
    cmd1 = HIGH;
  }
  if (digitalRead(optn) == LOW && optn1 == HIGH) {
    Keyboard.press(KEY_LEFT_ALT);
    Serial.println("OPTION");
    optn1 = LOW;
  } else if (digitalRead(optn) == HIGH && optn1 == LOW) {
    Keyboard.release(KEY_LEFT_ALT);
    optn1 = HIGH;
  }
  if (digitalRead(shift) == LOW && shift1 == HIGH) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Serial.println("SHIFT");
    shift1 = LOW;
  } else if (digitalRead(shift) == HIGH && shift1 == LOW) {
    Keyboard.release(KEY_LEFT_SHIFT);
    shift1 = HIGH;
  }
  if (digitalRead(capslock) == LOW && capslock1 == HIGH) {
    Keyboard.press(KEY_CAPS_LOCK);
    Serial.println("CAPS");
    capslock1 = LOW;
  } else if (digitalRead(capslock) == HIGH && capslock1 == LOW) {
    Keyboard.release(KEY_CAPS_LOCK);
    capslock1 = HIGH;
  }
}


void keypadEvent(char key, KeyState state) {
  switch (state) {

    case PRESSED:
      {
        int ke = key;
        Serial.print("PRESSED: ");
        Serial.print(key);  // as a character
        Serial.print(" - ");
        Serial.println((int)key);  // as a number
        Keyboard.press(ke);
      }
      break;

    case RELEASED:
      {
        int ke = key;
        Serial.print("RELEASED: ");
        Serial.print(key);  // as a character
        Serial.print(" - ");
        Serial.println((int)key);  // as a number
        Keyboard.release(ke);
      }
      break;

    default:
      break;
  }
}
