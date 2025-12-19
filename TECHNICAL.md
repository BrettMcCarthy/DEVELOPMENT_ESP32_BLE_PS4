# PS4 Controller Pairing and Bonding - Technical Documentation

## Overview

This library resolves pairing and bonding issues between PS4 DualShock 4 controllers and ESP32 WROOM Dev Kit V1 by implementing proper data structures and Bluetooth communication protocols.

## Key Components

### Data Structures

#### 1. Analog Input Structures
```c
typedef struct {
  int8_t lx;  // Left stick X-axis (-128 to 127)
  int8_t ly;  // Left stick Y-axis (-128 to 127)
  int8_t rx;  // Right stick X-axis (-128 to 127)
  int8_t ry;  // Right stick Y-axis (-128 to 127)
} ps4_analog_stick_t;

typedef struct {
  uint8_t l2;  // Left trigger (0 to 255)
  uint8_t r2;  // Right trigger (0 to 255)
} ps4_analog_button_t;

typedef struct {
  ps4_analog_stick_t stick;
  ps4_analog_button_t button;
} ps4_analog_t;
```

#### 2. Button State Structure
```c
typedef struct {
  uint8_t right : 1;
  uint8_t down : 1;
  uint8_t up : 1;
  uint8_t left : 1;
  uint8_t square : 1;
  uint8_t cross : 1;
  uint8_t circle : 1;
  uint8_t triangle : 1;
  uint8_t upright : 1;
  uint8_t downright : 1;
  uint8_t upleft : 1;
  uint8_t downleft : 1;
  uint8_t l1 : 1;
  uint8_t r1 : 1;
  uint8_t l2 : 1;
  uint8_t r2 : 1;
  uint8_t share : 1;
  uint8_t options : 1;
  uint8_t l3 : 1;
  uint8_t r3 : 1;
  uint8_t ps : 1;
  uint8_t touchpad : 1;
} ps4_button_t;
```

#### 3. Status and Sensor Structures
```c
typedef struct {
  uint8_t battery;
  uint8_t charging : 1;
  uint8_t audio : 1;
  uint8_t mic : 1;
} ps4_status_t;

typedef struct {
  int16_t x;
  int16_t y;
  int16_t z;
} ps4_sensor_accelerometer_t;

typedef struct {
  int16_t z;
} ps4_sensor_gyroscope_t;

typedef struct {
  ps4_sensor_accelerometer_t accelerometer;
  ps4_sensor_gyroscope_t gyroscope;
} ps4_sensor_t;
```

#### 4. Main Controller Data Structure
```c
typedef struct {
  ps4_analog_t analog;
  ps4_button_t button;
  ps4_status_t status;
  ps4_sensor_t sensor;
  uint8_t* latestPacket;
} ps4_t;
```

## Pairing and Bonding Implementation

### MAC Address Configuration

The library implements proper MAC address handling to ensure successful pairing:

```c
void ps4SetBluetoothMacAddress(const uint8_t* mac) {
  uint8_t baseMac[6];
  memcpy(baseMac, mac, 6);
  baseMac[5] -= 2;  // Adjust for ESP32 BT MAC address derivation
  esp_base_mac_addr_set(baseMac);
}
```

### Connection Management

The library handles connection events properly:

```c
void ps4ConnectEvent(uint8_t is_connected) {
    if (is_connected) {
        ps4Enable();  // Enable controller data streaming
    } else {
        is_active = false;  // Reset connection state
    }
}
```

### Event Processing

Events are processed with proper distinction between button press and release:

```c
typedef struct {
  ps4_button_t button_down;  // Button press events
  ps4_button_t button_up;    // Button release events
  ps4_analog_t analog_move;  // Analog movement events
} ps4_event_t;
```

## Bluetooth Protocol Implementation

### L2CAP Services

The library initializes two L2CAP services:
- HID Control (PSM 0x0011)
- HID Interrupt (PSM 0x0013)

### HID Commands

#### Enable Command
```c
static const uint8_t hid_cmd_payload_ps4_enable[] = {0x43, 0x02};
```

#### Control Command Structure
```c
typedef struct {
  uint8_t code;
  uint8_t identifier;
  uint8_t data[PS4_SEND_BUFFER_SIZE];
} hid_cmd_t;
```

### Packet Format

The library parses 50-byte HID packets:
- Bytes 13-16: Analog stick values
- Bytes 17-19: Button states
- Bytes 20-21: Trigger values
- Byte 42: Status (battery, charging)

## Usage Examples

### Basic Connection
```cpp
#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);
  PS4.begin();
}

void loop() {
  if (PS4.isConnected()) {
    if (PS4.Cross()) {
      Serial.println("Cross pressed!");
    }
  }
}
```

### Advanced Usage with Callbacks
```cpp
void onConnect() {
  Serial.println("Controller connected!");
  PS4.setLed(0, 255, 0);
}

void setup() {
  PS4.attachOnConnect(onConnect);
  PS4.begin("01:02:03:04:05:06");
}
```

## Troubleshooting

### Pairing Issues
1. Verify MAC address matches using SixaxisPairTool
2. Erase ESP32 flash if bonding data is corrupted
3. Ensure Bluetooth Classic is enabled (not BLE only)

### Connection Drops
1. Check power supply stability
2. Reduce Bluetooth interference
3. Maintain line of sight within 10m

### Button Events Not Working
- Fixed: button_up events now correctly assigned to ps4Event.button_up
- Fixed: GAP event constants corrected

## Performance Characteristics

- Latency: ~10ms typical
- Update Rate: ~100Hz
- Range: Up to 10 meters
- Battery Life: 4-8 hours typical

## Memory Usage

- Flash: ~300KB
- RAM: ~50KB during operation
- Stack: ~8KB per connection

## Security Considerations

- No authentication by default (BTM security level 0)
- MAC address pairing provides basic security
- Consider implementing custom authentication for production use

## Future Enhancements

Potential improvements:
1. Multi-controller support
2. Touchpad coordinate tracking
3. Audio streaming support
4. Motion gesture recognition
5. Custom HID report handling

## References

- PS4 Controller HID Report Descriptor
- ESP32 Bluetooth Classic API Documentation
- L2CAP Protocol Specification
- HID Profile Specification
