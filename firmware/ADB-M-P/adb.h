#ifndef ADB_h
#define ADB_h

#include <Arduino.h>
#include "driver/gpio.h"
#include <cstdint>

#define ADB_DATA_PIN GPIO_NUM_36
#define ADB_LOW() \
  do { \
    gpio_set_direction(ADB_DATA_PIN, GPIO_MODE_OUTPUT); \
    gpio_set_level(ADB_DATA_PIN, 0); \
  } while (0)
#define ADB_HIGH() \
  do { gpio_set_direction(ADB_DATA_PIN, GPIO_MODE_INPUT); } while (0)
#define ADB_READ() (gpio_get_level(ADB_DATA_PIN))
#define ADB_MOUSE_CONV_AXIS(x)  (int8_t)(x << 1)
#define ADB_POLL_DELAY 5

#define ADB_ADDRESS(addr) (addr << 4)
#define ADB_REGISTER(reg) (reg)
#define ADB_CMD_TALK (0b11 << 2)
#define ADB_CMD_LISTEN (0b10 << 2)
#define ADB_CMD_FLUSH (0b01 << 2)

#define ADB_ADDR_MOUSE 3

#define ADB_BIT_ERROR 0xFF

// Reset: signal low for 3 ms.
static void adb_reset() {
  ADB_LOW();
  delayMicroseconds(3000);
  ADB_HIGH();
}

// Attention: signal low for 800 μs.
static void adb_attention() {
  ADB_LOW();
  delayMicroseconds(800);
  ADB_HIGH();
}

// Sync: signal high for 70 μs.
static void adb_sync() {
  ADB_HIGH();
  delayMicroseconds(70);
}

// Send a single on ADB_DATA_PIN.
// '0' if bit == 0x0: write 65 μs LOW, 35 μs HIGH.
// '1' if bit >= 0x1: write 35 μs LOW, 65 μs HIGH.
static void adb_write_bit(uint16_t bit) {
  if (bit) {  // '1' bit
    ADB_LOW();
    delayMicroseconds(35);

    ADB_HIGH();
    delayMicroseconds(65);
  } else {  // '0' bit
    ADB_LOW();
    delayMicroseconds(65);

    ADB_HIGH();
    delayMicroseconds(35);
  }
}

// Send `length` least significant bits from `bits`,
// starting with the most significant bit.
static void adb_write_bits(uint16_t bits, uint8_t length) {
  uint16_t mask = 1 << (length - 1);
  while (mask) {
    adb_write_bit(bits & mask);
    mask >>= 1;
  }
}

// Like adb_write_bits, but add start and stop bits
static void adb_write_data_packet(uint16_t bits, uint8_t length) {
  adb_write_bit(1);
  adb_write_bits(bits, length);
  adb_write_bit(0);
}

// Send the '0' stop bit, and listen for an SRQ.
// ``If a device in need of service issues a service request,
// it must do so within the 65 μs of the Stop Bit’s low time
// and maintain the line low for a total of 300 μs.''
// Returns true if there was an SRQ.
static bool adb_stop_bit_srq_listen() {
  adb_write_bit(0);
  // TODO: Properly handle SRQ, currently waits it out:
  auto time_end_stop_bit = micros();
  while (ADB_READ() == LOW && micros() - time_end_stop_bit < 300 - 35) {  // TODO: does it make sense to timeout?
    delayMicroseconds(5);
  }
  return false;
}

// Write a command to the bus.
void adb_write_command(uint8_t command_byte) {
  adb_attention();
  adb_sync();
  adb_write_bits((uint16_t)command_byte, 8);
  adb_stop_bit_srq_listen();  // TODO: Handle the SRQ
}

// Stop-to-start time: period of 140 - 260 μs before device's
// response when the bus is held high.
// Returns: true if the response is starting, false if timeout
static bool adb_wait_tlt(bool response_expected) {
  ADB_HIGH();
  if (!response_expected) {
    delayMicroseconds(200);
    return true;
  }
  delayMicroseconds(80);
  unsigned long start = micros();
  while (ADB_READ() == HIGH) {
    if (micros() - start > 200) return false;
  }
  return true;
}


// Read a single bit from the bus.
static uint8_t adb_read_bit() {
  auto time_start = micros();

  while (ADB_READ() == LOW) {
    // devices need to stick to 30% precision, 65 * 1.3 = 85 μs
    // if this time is exceeded assume timeout
    if (micros() - time_start > 85)
      return ADB_BIT_ERROR;
  }
  auto low_time = micros() - time_start;

  while (ADB_READ() == HIGH) {
    // devices need to stick to 30% precision, 65 * 1.3 = 85 μs
    // if this time is exceeded assume timeout
    if (micros() - time_start - low_time > 85)
      return ADB_BIT_ERROR;
  }
  auto high_time = micros() - time_start - low_time;

  return (low_time < high_time) ? 0x1 : 0x0;
}

// Read `length` bits from the bus into `buffer`.
bool adb_read_data_packet(uint16_t* buffer, uint8_t length) {
  if (adb_read_bit() != 0x1) {  // start bit should equal to '1'
    return false;
  }

  *buffer = 0;
  for (uint8_t i = 0; i < length; i++) {
    uint8_t current_bit = adb_read_bit();
    if (current_bit == ADB_BIT_ERROR) {
      return false;
    }
    *buffer <<= 1;
    *buffer |= current_bit;
  }

  auto stop_start = micros();
  while (ADB_READ() == 0 && micros() - stop_start < 90)
    ;
  return true;
}

void adb_init() {
  gpio_reset_pin(ADB_DATA_PIN);
  ADB_HIGH();
  delay(10);

  adb_reset();
}

struct adb_mouse_data {
    uint8_t x_offset : 7;   // 6 - 0
    uint8_t reserved0 : 1;  // 7
    uint8_t y_offset : 7;   // 14 - 8
    bool button : 1;        // 15
};

// Contains device info and params
struct adb_register3 {
    uint8_t device_handler_id : 8;
    uint8_t device_address : 4;
    uint8_t reserved1 : 1;         // must be 0
    uint8_t srq_enable : 1;
    uint8_t exceptional_event : 1; // device specific, always 1 if not used
    uint8_t reserved0 : 1;         // must be 0
};

template <typename T>
union adb_data {
    uint16_t raw;
    T data;
};

adb_data<adb_register3> adb_device_read_register3(uint8_t addr, bool* error) {
  adb_data<adb_register3> reg3 = { 0 };
  portDISABLE_INTERRUPTS();
  adb_write_command(ADB_CMD_TALK | ADB_ADDRESS(addr) | ADB_REGISTER(3));
  *error = !adb_wait_tlt(true) || !adb_read_data_packet(&reg3.raw, 16);
  portENABLE_INTERRUPTS();
  return reg3;
}


bool adb_device_update_register3(uint8_t addr, adb_data<adb_register3> new_reg3, uint16_t mask, bool* error) {
  // Read the initial value
  adb_data<adb_register3> reg3 = adb_device_read_register3(addr, error);
  if (*error) return false;
  delay(ADB_POLL_DELAY);

  // Apply the change
  reg3.raw = (reg3.raw & ~mask) | (new_reg3.raw & mask);

  // Write the new value
  portDISABLE_INTERRUPTS();
  adb_write_command(ADB_CMD_LISTEN | ADB_ADDRESS(addr) | ADB_REGISTER(3));
  adb_wait_tlt(false);
  adb_write_data_packet(reg3.raw, 16);
  portENABLE_INTERRUPTS();
  delay(ADB_POLL_DELAY);

  // Read the current value
  reg3 = adb_device_read_register3(addr, error);
  if (*error) return false;

  // Check if update worked, return true
  if ((reg3.raw & mask) == (new_reg3.raw & mask))
    return true;

  return false;
}


#ifdef PIO_FRAMEWORK_ARDUINO_ENABLE_CDC
void print16b(uint16_t buff) {
  uint16_t mask = (1 << 15);
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buff & mask ? '1' : '0');
    mask >>= 1;
  }
  Serial.write('\n');
  Serial.flush();
}
#endif

adb_data<adb_mouse_data> adb_mouse_read_data(bool* error) {
  adb_data<adb_mouse_data> mouse_data = { 0 };
  portDISABLE_INTERRUPTS();
  adb_write_command(ADB_CMD_TALK | ADB_ADDRESS(ADB_ADDR_MOUSE) | ADB_REGISTER(0));
  *error = !adb_wait_tlt(true) || !adb_read_data_packet(&mouse_data.raw, 16);
  portENABLE_INTERRUPTS();
  return mouse_data;
}

#endif