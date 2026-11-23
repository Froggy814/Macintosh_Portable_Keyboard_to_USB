#include "adb.h"
#include "USB.h"
#include "USBHIDMouse.h"

USBHIDMouse Mouse;

#define POLL_DELAY 5
bool mouse_present = false;

void setup() {

  Serial.begin(115200);

  Mouse.begin();
  USB.begin();

  // Set up the ADB bus
  adb_init();

  delay(1000);  // A wait for good measure, apparently AEKII can take a moment to reset

  // Initialise the ADB devices
  bool error = false;

  if (!error) mouse_present = true;
}

void mouse_handler() {
  static bool last_btn = false;
  bool error = false;
  auto mouse_data = adb_mouse_read_data(&error);


  if (error) return;

  int8_t mouse_x = ADB_MOUSE_CONV_AXIS(mouse_data.data.x_offset);
  int8_t mouse_y = ADB_MOUSE_CONV_AXIS(mouse_data.data.y_offset);
  bool btn_pressed = !(mouse_data.raw & 0x8000);



  if (btn_pressed != last_btn) {
    if (btn_pressed) Mouse.press(MOUSE_LEFT);
    else Mouse.release(MOUSE_LEFT);
    last_btn = btn_pressed;
  }

  if (mouse_x != 0 || mouse_y != 0) {
    Mouse.move(mouse_x, mouse_y, 0);
  }
}


void loop() {
  if (mouse_present) {
    mouse_handler();
    delay(POLL_DELAY);
  }
}
