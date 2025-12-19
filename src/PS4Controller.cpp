#include "PS4Controller.h"

#ifdef ARDUINO_ARCH_ESP32
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"
#endif

ps4_t PS4Controller::data;
ps4_event_t PS4Controller::event;
void (*PS4Controller::_callback)(uint8_t) = nullptr;
void (*PS4Controller::_onConnect)() = nullptr;
void (*PS4Controller::_onDisconnect)() = nullptr;

bool PS4Controller::begin(const char* mac) {
  ps4Init();
  
  if (mac && mac[0] != '\0') {
    uint8_t addr[6];
    sscanf(mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &addr[5], &addr[4], &addr[3], &addr[2], &addr[1], &addr[0]);
    ps4SetBluetoothMacAddress(addr);
  }
  
  ps4SetEventCallback(defaultEventCallback);
  ps4SetConnectionCallback(defaultConnectionCallback);
  ps4Enable();
  
  return true;
}

bool PS4Controller::isConnected() {
  return ps4IsConnected();
}

void PS4Controller::attach(void (*userFunction)(uint8_t)) {
  _callback = userFunction;
}

void PS4Controller::attachOnConnect(void (*userFunction)()) {
  _onConnect = userFunction;
}

void PS4Controller::attachOnDisconnect(void (*userFunction)()) {
  _onDisconnect = userFunction;
}

void PS4Controller::setLed(uint8_t red, uint8_t green, uint8_t blue) {
  ps4SetLed(red, green, blue);
}

void PS4Controller::setRumble(uint8_t smallRumble, uint8_t largeRumble) {
  ps4_cmd_t cmd;
  cmd.smallRumble = smallRumble;
  cmd.largeRumble = largeRumble;
  cmd.r = 0;
  cmd.g = 0;
  cmd.b = 0;
  cmd.flashOn = 0;
  cmd.flashOff = 0;
  ps4Cmd(cmd);
}

void PS4Controller::setFlashRate(uint8_t onTime, uint8_t offTime) {
  ps4_cmd_t cmd;
  cmd.smallRumble = 0;
  cmd.largeRumble = 0;
  cmd.r = 0;
  cmd.g = 0;
  cmd.b = 0;
  cmd.flashOn = onTime;
  cmd.flashOff = offTime;
  ps4Cmd(cmd);
}

void PS4Controller::sendToController() {
  ps4_cmd_t cmd;
  cmd.smallRumble = 0;
  cmd.largeRumble = 0;
  cmd.r = 0;
  cmd.g = 0;
  cmd.b = 0;
  cmd.flashOn = 0;
  cmd.flashOff = 0;
  ps4Cmd(cmd);
}

void PS4Controller::defaultEventCallback(ps4_t controller, ps4_event_t eventData) {
  data = controller;
  event = eventData;
}

void PS4Controller::defaultConnectionCallback(uint8_t isConnected) {
  if (_callback != nullptr) {
    _callback(isConnected);
  }
  
  if (isConnected && _onConnect != nullptr) {
    _onConnect();
  } else if (!isConnected && _onDisconnect != nullptr) {
    _onDisconnect();
  }
}

PS4Controller PS4;
