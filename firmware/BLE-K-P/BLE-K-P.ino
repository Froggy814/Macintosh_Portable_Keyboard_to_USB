#include <Keypad.h>
#include <HijelHID_BLEKeyboard.h>

HijelHID_BLEKeyboard bleKeyboard("Mac Portable KBD", "Frogtronics", 100);

#define capslock 42
#define shift 41
#define ctrl 40
#define optn 39
#define cmd 38

const byte ROWS = 11;
const byte COLS = 8;
bool capslock1 = HIGH;
bool shift1 = HIGH;
bool ctrl1 = HIGH;
bool optn1 = HIGH;
bool cmd1 = HIGH;

byte rowPins[ROWS] = { 4, 5, 6, 7, 15, 16, 17, 18, 8, 3, 37 };
byte colPins[COLS] = { 9, 10, 11, 12, 13, 14, 1, 2 };

char hexaKeys[ROWS][COLS] = {
  /* X0  */ { KEY_KP_1, KEY_NUM_LOCK, KEY_KP_3, 0, KEY_TAB, KEY_LEFT, 'a', 0 },
  /* X1  */ { 0, KEY_KP_2, 0, KEY_KP_4, KEY_Q, 0, KEY_S, KEY_Z },
  /* X2  */ { KEY_KP_ENTER, 0, 0, 0, KEY_W, KEY_UP, KEY_DOWN, KEY_X },
  /* X3  */ { KEY_KP_EQUAL, KEY_KP_6, 0, KEY_KP_MINUS, KEY_E, KEY_D, 0, KEY_C },
  /* X4  */ { KEY_KP_0, 0, KEY_KP_8, 0, KEY_R, KEY_RIGHT, KEY_F, KEY_V },
  /* X5  */ { 0, KEY_KP_7, KEY_KP_DOT, KEY_KP_9, KEY_KP_ENTER, KEY_U, KEY_B, KEY_SPACE },
  /* X6  */ { KEY_ESCAPE, KEY_1, KEY_2, KEY_3, KEY_I, KEY_BACKSPACE, KEY_H, 0 },
  /* X7  */ { KEY_4, KEY_GRAVE, KEY_G, KEY_BACKSLASH, KEY_K, KEY_L, KEY_J, KEY_N },
  /* X8  */ { KEY_5, KEY_T, KEY_Y, KEY_LEFTBRACE, KEY_P, KEY_SEMICOLON, KEY_COMMA, KEY_M },
  /* X9  */ { KEY_6, KEY_7, KEY_8, KEY_9, KEY_RIGHTBRACE, KEY_APOSTROPHE, KEY_SLASH, 0 },
  /* X10 */ { KEY_EQUAL, KEY_MINUS, KEY_0, KEY_O, 0, KEY_RETURN, KEY_DOT, 0 }
};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup() {
  Serial.begin(115200);
  customKeypad.addStatedEventListener(keypadEvent);
  customKeypad.setDebounceTime(2);
  customKeypad.setHoldTime(500);
  bleKeyboard.begin();

  pinMode(ctrl, INPUT_PULLUP);
  pinMode(shift, INPUT_PULLUP);
  pinMode(cmd, INPUT_PULLUP);
  pinMode(optn, INPUT_PULLUP);
  pinMode(capslock, INPUT_PULLUP);
}

void loop() {

  if (bleKeyboard.isConnected()) {
    customKeypad.getKeys();
    specialKeys();
  }
}

void specialKeys() {

  if (digitalRead(ctrl) == LOW && ctrl1 == HIGH) {
    bleKeyboard.press(KEY_LCTRL);
    Serial.println("CTRL");
    ctrl1 = LOW;
  } else if (digitalRead(ctrl) == HIGH && ctrl1 == LOW) {
    bleKeyboard.release(KEY_LCTRL);
    ctrl1 = HIGH;
  }
  if (digitalRead(cmd) == LOW && cmd1 == HIGH) {
    bleKeyboard.press(KEY_LGUI);
    Serial.println("CMD");
    cmd1 = LOW;
  } else if (digitalRead(cmd) == HIGH && cmd1 == LOW) {
    bleKeyboard.release(KEY_LGUI);
    cmd1 = HIGH;
  }
  if (digitalRead(optn) == LOW && optn1 == HIGH) {
    bleKeyboard.press(KEY_LALT);
    Serial.println("OPTION");
    optn1 = LOW;
  } else if (digitalRead(optn) == HIGH && optn1 == LOW) {
    bleKeyboard.release(KEY_LALT);
    optn1 = HIGH;
  }
  if (digitalRead(shift) == LOW && shift1 == HIGH) {
    bleKeyboard.press(KEY_LSHIFT);
    Serial.println("SHIFT");
    shift1 = LOW;
  } else if (digitalRead(shift) == HIGH && shift1 == LOW) {
    bleKeyboard.release(KEY_LSHIFT);
    shift1 = HIGH;
  }
  if (digitalRead(capslock) == LOW && capslock1 == HIGH) {
    bleKeyboard.press(KEY_CAPS_LOCK);
    Serial.println("CAPS");
    capslock1 = LOW;
  } else if (digitalRead(capslock) == HIGH && capslock1 == LOW) {
    bleKeyboard.release(KEY_CAPS_LOCK);
    capslock1 = HIGH;
  }
}

void keypadEvent(char key, KeyState state) {
  switch (state) {

    case PRESSED:
      {
        byte ke = key;
        if (key == 'a') {
          ke = KEY_A;
        }
        Serial.print("PRESSED: ");
        Serial.print(key);  // as a character
        Serial.print(" - ");
        Serial.println((int)key);  // as a number
        bleKeyboard.press(ke);
        delay(50);
      }
      break;

    case RELEASED:
      {
        byte ke = key;
        if (key == 'a') {
          ke = KEY_A;
        }
        Serial.print("RELEASED: ");
        Serial.print(key);  // as a character
        Serial.print(" - ");
        Serial.println((int)key);  // as a number
        bleKeyboard.release(ke);
        delay(50);
      }
      break;

    default:
      break;
  }
}