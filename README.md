# ESP32 PS4 Controller Library

A comprehensive library for connecting PS4 DualShock 4 controllers to ESP32 WROOM Dev Kit V1 via Bluetooth. This library resolves pairing and bonding issues with updated data structures for reliable controller communication.

## Features

- ✅ Full PS4 DualShock 4 controller support
- ✅ Updated data structures for reliable pairing and bonding
- ✅ All button and analog stick inputs
- ✅ Sensor data (accelerometer and gyroscope)
- ✅ LED color control
- ✅ Rumble/vibration control
- ✅ Battery status monitoring
- ✅ Connection callbacks
- ✅ ESP32 WROOM Dev Kit V1 compatible

## Data Structures

### Core Types

```c
// Analog stick positions (-128 to 127)
typedef struct {
  int8_t lx, ly;  // Left stick
  int8_t rx, ry;  // Right stick
} ps4_analog_stick_t;

// Analog trigger values (0 to 255)
typedef struct {
  uint8_t l2, r2;
} ps4_analog_button_t;

// All button states (bit fields)
typedef struct {
  uint8_t right : 1, down : 1, up : 1, left : 1;
  uint8_t square : 1, cross : 1, circle : 1, triangle : 1;
  uint8_t l1 : 1, r1 : 1, l2 : 1, r2 : 1;
  uint8_t share : 1, options : 1, l3 : 1, r3 : 1;
  uint8_t ps : 1, touchpad : 1;
} ps4_button_t;

// Controller status
typedef struct {
  uint8_t battery;
  uint8_t charging : 1;
  uint8_t audio : 1;
  uint8_t mic : 1;
} ps4_status_t;

// Sensor data
typedef struct {
  int16_t x, y, z;  // Accelerometer
} ps4_sensor_accelerometer_t;

typedef struct {
  int16_t z;  // Gyroscope
} ps4_sensor_gyroscope_t;
```

## Installation

### Arduino IDE

1. Download this repository as a ZIP file
2. In Arduino IDE, go to Sketch → Include Library → Add .ZIP Library
3. Select the downloaded ZIP file
4. Restart Arduino IDE

### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps = 
    https://github.com/BrettMcCarthy/DEVELOPMENT_ESP32_BLE_PS4
```

## Pairing Your PS4 Controller

### Step 1: Get Your ESP32 MAC Address

Upload this simple sketch to get your ESP32's Bluetooth MAC address:

```cpp
#include "esp_bt_device.h"

void setup() {
  Serial.begin(115200);
  esp_bt_dev_get_address();
}

void loop() {}
```

### Step 2: Pair Controller to ESP32

1. Download and install [SixaxisPairTool](https://github.com/user-attachments/files/16462237/SixaxisPairTool.zip) (Windows) or similar tool
2. Connect your PS4 controller via USB
3. Run SixaxisPairTool
4. Enter your ESP32's MAC address
5. Click "Update"
6. Disconnect the USB cable

### Step 3: Test Connection

Upload an example sketch and press the PS button on the controller. It should connect within a few seconds.

## Quick Start

```cpp
#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);
  PS4.begin();
  Serial.println("Waiting for PS4 controller...");
}

void loop() {
  if (PS4.isConnected()) {
    if (PS4.Cross()) {
      Serial.println("Cross pressed!");
    }
    
    Serial.printf("Left Stick: X=%d, Y=%d\n", 
                  PS4.LStickX(), PS4.LStickY());
  }
  delay(100);
}
```

## API Reference

### Initialization

- `PS4.begin()` - Initialize with default MAC address
- `PS4.begin("01:02:03:04:05:06")` - Initialize with specific MAC address
- `PS4.isConnected()` - Check if controller is connected

### Callbacks

- `PS4.attach(callback)` - Attach connection/disconnection callback
- `PS4.attachOnConnect(callback)` - Attach connect callback
- `PS4.attachOnDisconnect(callback)` - Attach disconnect callback

### Buttons

- `PS4.Cross()`, `PS4.Circle()`, `PS4.Triangle()`, `PS4.Square()`
- `PS4.Up()`, `PS4.Down()`, `PS4.Left()`, `PS4.Right()`
- `PS4.L1()`, `PS4.R1()`, `PS4.L2()`, `PS4.R2()`
- `PS4.L3()`, `PS4.R3()` - Analog stick buttons
- `PS4.Share()`, `PS4.Options()`
- `PS4.PSButton()`, `PS4.Touchpad()`

### Analog Inputs

- `PS4.LStickX()`, `PS4.LStickY()` - Left stick (-128 to 127)
- `PS4.RStickX()`, `PS4.RStickY()` - Right stick (-128 to 127)
- `PS4.L2Value()`, `PS4.R2Value()` - Trigger values (0 to 255)

### Sensors

- `PS4.SensorX()`, `PS4.SensorY()`, `PS4.SensorZ()` - Accelerometer
- `PS4.GyroZ()` - Gyroscope Z-axis

### Status

- `PS4.Battery()` - Battery level (0-255)
- `PS4.Charging()` - Charging status
- `PS4.Audio()`, `PS4.Mic()` - Audio/mic status

### Output

- `PS4.setLed(r, g, b)` - Set LED color (0-255)
- `PS4.setRumble(small, large)` - Set rumble intensity (0-255)
- `PS4.setFlashRate(onTime, offTime)` - Set LED flash rate

## Examples

See the `examples/` folder for:
- `PS4Controller_Basic` - Simple button and stick reading
- `PS4Controller_Advanced` - Full feature demonstration with callbacks and sensors

## Troubleshooting

### Controller Won't Connect

1. Verify MAC address is correct
2. Ensure controller is paired using SixaxisPairTool
3. Try erasing ESP32 flash: `esptool.py erase_flash`
4. Re-upload sketch
5. Press and hold PS button for 10+ seconds to reset controller

### Frequent Disconnections

1. Ensure adequate power supply to ESP32
2. Check for Bluetooth interference
3. Keep controller within range (< 10 meters)
4. Verify battery level

### Pairing Issues

1. Delete old bonding data by erasing flash
2. Re-pair controller with updated MAC address
3. Ensure Bluetooth Classic is enabled in ESP32 configuration

## Technical Details

### Bluetooth Configuration

This library requires ESP32 Bluetooth Classic (BR/EDR) support. Ensure your ESP32 board configuration includes:

```
CONFIG_BTDM_CONTROLLER_MODE_BTDM=y
```

### Memory Requirements

- Flash: ~300KB
- RAM: ~50KB during operation

### Compatibility

- ✅ ESP32 WROOM Dev Kit V1
- ✅ ESP32 DevKit V1
- ✅ ESP32-WROOM-32
- ⚠️ ESP32-S2/S3/C3 (No Bluetooth Classic support)

## Credits

Based on the work from:
- [aed3/PS4-esp32](https://github.com/aed3/PS4-esp32)
- ARES_Hexapod project

## License

This library is open source. See LICENSE file for details.

## Contributing

Contributions are welcome! Please open an issue or pull request on GitHub.
