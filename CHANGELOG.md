# Changelog

All notable changes to this project will be documented in this file.

## [1.0.0] - 2025-12-19

### Added
- Complete PS4 Controller data structure implementation
  - `ps4_analog_stick_t`: Analog stick position tracking
  - `ps4_analog_button_t`: Trigger pressure values
  - `ps4_button_t`: All 22 button states with bit fields
  - `ps4_status_t`: Battery, charging, audio, mic status
  - `ps4_sensor_t`: Accelerometer and gyroscope data
  - `ps4_cmd_t`: Command structure for LED, rumble, flash control
  - `ps4_event_t`: Event tracking for button press/release
  - `ps4_t`: Main controller data structure

- Core functionality implementation
  - `ps4.c`: Core PS4 controller functions
  - `ps4_parser.c`: Packet parsing and event generation
  - `ps4_l2cap.c`: L2CAP protocol handling
  - `ps4_spp.c`: SPP initialization and Bluetooth setup

- Arduino wrapper library
  - `PS4Controller.h`: Arduino-friendly API
  - `PS4Controller.cpp`: Implementation with callbacks

- Stack and helper files
  - `stack/`: Bluetooth stack header files
  - `osi/`: Memory allocator helper

- Example sketches
  - `PS4Controller_Basic`: Simple button and analog reading
  - `PS4Controller_Advanced`: Full feature demonstration with callbacks

- Documentation
  - Comprehensive README with setup instructions
  - Technical documentation (TECHNICAL.md)
  - Arduino keywords.txt for syntax highlighting
  - Library.properties for Arduino Library Manager

### Fixed
- Button up events now correctly assigned to `ps4Event.button_up` instead of `ps4Event.button_down`
- Corrected `GAP_EVT_CONN_UNCONGESTED` constant from `0x01043` to `0x0104`
- Removed extra backslash from error logging in ps4_l2cap.c
- Fixed typo in btm_api.h comment ("nad" → "and")

### Changed
- Updated README with comprehensive pairing and troubleshooting guide
- Improved data structure organization for better maintainability

## Pairing and Bonding Improvements

### MAC Address Handling
- Proper MAC address configuration with base address adjustment
- Support for custom MAC address pairing via SixaxisPairTool

### Connection Management
- Robust connection state tracking
- Automatic controller enable on connection
- Proper disconnection handling

### Event Processing
- Separate button press and release event tracking
- Analog movement detection
- Real-time sensor data processing

### Bluetooth Protocol
- L2CAP service initialization (HID Control and Interrupt)
- HID command packet structure
- 50-byte packet parsing with correct field offsets

## Known Issues
None at this time.

## Compatibility
- ✅ ESP32 WROOM Dev Kit V1
- ✅ ESP32 DevKit V1
- ✅ ESP32-WROOM-32
- ❌ ESP32-S2/S3/C3 (No Bluetooth Classic support)

## Credits
Based on the excellent work from:
- [aed3/PS4-esp32](https://github.com/aed3/PS4-esp32)
- ARES_Hexapod project

## License
Open source - See LICENSE file for details.
