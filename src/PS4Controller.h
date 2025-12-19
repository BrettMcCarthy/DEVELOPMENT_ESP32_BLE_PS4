#ifndef PS4_CONTROLLER_H
#define PS4_CONTROLLER_H

#include "ps4.h"

class PS4Controller {
 public:
  // Initialize the PS4 controller library
  static bool begin(const char* mac = "");
  
  // Check if the controller is connected
  static bool isConnected();
  
  // Attach a callback function to trigger when a PS4 controller connects or
  // disconnects
  static void attach(void (*userFunction)(uint8_t));
  
  // Attach a callback function to trigger on new events. Provides additional
  // event data
  static void attachOnConnect(void (*userFunction)());
  static void attachOnDisconnect(void (*userFunction)());
  
  // Set the rumble and lightbar of the controller
  static void setLed(uint8_t red, uint8_t green, uint8_t blue);
  static void setRumble(uint8_t smallRumble, uint8_t largeRumble);
  static void setFlashRate(uint8_t onTime, uint8_t offTime);
  
  // Send the output command
  static void sendToController();
  
  // Button states
  static bool Left() { return data.button.left; }
  static bool Down() { return data.button.down; }
  static bool Right() { return data.button.right; }
  static bool Up() { return data.button.up; }
  
  static bool Square() { return data.button.square; }
  static bool Cross() { return data.button.cross; }
  static bool Circle() { return data.button.circle; }
  static bool Triangle() { return data.button.triangle; }
  
  static bool UpLeft() { return data.button.upleft; }
  static bool UpRight() { return data.button.upright; }
  static bool DownLeft() { return data.button.downleft; }
  static bool DownRight() { return data.button.downright; }
  
  static bool L1() { return data.button.l1; }
  static bool L2() { return data.button.l2; }
  static bool L3() { return data.button.l3; }
  
  static bool R1() { return data.button.r1; }
  static bool R2() { return data.button.r2; }
  static bool R3() { return data.button.r3; }
  
  static bool Share() { return data.button.share; }
  static bool Options() { return data.button.options; }
  static bool PSButton() { return data.button.ps; }
  static bool Touchpad() { return data.button.touchpad; }
  
  // Analog stick values (-128 to 127)
  static int8_t LStickX() { return data.analog.stick.lx; }
  static int8_t LStickY() { return data.analog.stick.ly; }
  static int8_t RStickX() { return data.analog.stick.rx; }
  static int8_t RStickY() { return data.analog.stick.ry; }
  
  // Analog button values (0 to 255)
  static uint8_t L2Value() { return data.analog.button.l2; }
  static uint8_t R2Value() { return data.analog.button.r2; }
  
  // Status information
  static uint8_t Battery() { return data.status.battery; }
  static bool Charging() { return data.status.charging; }
  static bool Audio() { return data.status.audio; }
  static bool Mic() { return data.status.mic; }
  
  // Sensor data
  static int16_t SensorX() { return data.sensor.accelerometer.x; }
  static int16_t SensorY() { return data.sensor.accelerometer.y; }
  static int16_t SensorZ() { return data.sensor.accelerometer.z; }
  static int16_t GyroZ() { return data.sensor.gyroscope.z; }
  
  static ps4_t data;
  static ps4_event_t event;
  
 private:
  static void (*_callback)(uint8_t);
  static void (*_onConnect)();
  static void (*_onDisconnect)();
  
  static void defaultEventCallback(ps4_t controller, ps4_event_t eventData);
  static void defaultConnectionCallback(uint8_t isConnected);
};

// Easier syntax for Arduino sketches
extern PS4Controller PS4;

#endif
