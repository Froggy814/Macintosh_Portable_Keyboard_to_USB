#include <KeyMatrix.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#define capslock 42
#define shift 41
#define ctrl 40
#define optn 39
#define cmd 38

int rows = 11;
int cols = 8;
int rowsPins[] = { 4, 5, 6, 7, 15, 16, 17, 18, 8, 3, 46 };
int colsPins[] = { 9, 10, 11, 12, 13, 14, 1, 2 };
char keymap[11][8] = {
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

void ONpress(char key) {
  Serial.print("PRESSED: ");
  Serial.print(key);  // as a character
  Serial.print("  (");
  Serial.print((int)key);  // as a number
  Serial.println(")");
  Keyboard.press(key);
  Serial.println(key);
}

void ONrelease(char key) {
  Serial.print("RELEASED: ");
  Serial.print(key);
  Serial.print("  (");
  Serial.print((int)key);
  Serial.println(")");
  Keyboard.release(key);
}

void whenPressed(char key) {
  Serial.print("REPEAT: ");
  Serial.print(key);
  Serial.print("  (");
  Serial.print((int)key);
  Serial.println(")");
}

void specialKeys() {
  if (digitalRead(ctrl) == LOW) {
    Keyboard.press(KEY_LEFT_CTRL);
    Serial.println("CTRL");
  } else {
    Keyboard.release(KEY_LEFT_CTRL);
  }
    if (digitalRead(cmd) == LOW) {
    Keyboard.press(KEY_LEFT_GUI);
    Serial.println("CMD");
  } else {
    Keyboard.release(KEY_LEFT_GUI);
  }
    if (digitalRead(optn) == LOW) {
    Keyboard.press(KEY_LEFT_ALT);
    Serial.println("OPTION");
  } else {
    Keyboard.release(KEY_LEFT_ALT);
  }
    if (digitalRead(shift) == LOW) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Serial.println("SHIFT");
  } else {
    Keyboard.release(KEY_LEFT_SHIFT);
  }
    if (digitalRead(capslock) == LOW) {
    Keyboard.press(KEY_CAPS_LOCK);
    Serial.println("CAPS");
  } else if (digitalRead(capslock) == HIGH) {
    Keyboard.release(KEY_CAPS_LOCK);
  }
}
KeyMatrix keypad(rows, cols, (int*)rowsPins, (int*)colsPins, (char*)keymap);
void setup() {
  Serial.begin(9600);
  keypad.onRelease(&ONrelease);
  keypad.onPress(&ONpress);
  keypad.whenPressed(&whenPressed, 500);
  keypad.setDebounce(2);
  Keyboard.begin();
  USB.begin();

  pinMode(ctrl, INPUT_PULLUP);
  pinMode(shift, INPUT_PULLUP);
  pinMode(cmd, INPUT_PULLUP);
  pinMode(optn, INPUT_PULLUP);
  pinMode(capslock, INPUT_PULLUP);
}

void loop() {
  keypad.update();
  specialKeys();
}