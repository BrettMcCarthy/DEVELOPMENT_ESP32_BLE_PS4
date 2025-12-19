#include <PS4Controller.h>

// Callback function when controller connects
void onConnect() {
  Serial.println("PS4 Controller Connected!");
  // Set LED to green when connected
  PS4.setLed(0, 255, 0);
}

// Callback function when controller disconnects
void onDisconnect() {
  Serial.println("PS4 Controller Disconnected!");
}

void setup() {
  Serial.begin(115200);
  
  // Attach callback functions
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisconnect);
  
  // Initialize PS4 controller with specific MAC address
  // Replace with your ESP32's MAC address
  // You can get this by calling esp_bt_dev_get_address()
  PS4.begin("01:02:03:04:05:06");
  
  Serial.println("PS4 Controller Advanced Example");
  Serial.println("Waiting for PS4 controller...");
}

void loop() {
  if (PS4.isConnected()) {
    // D-Pad controls
    if (PS4.Up()) {
      Serial.println("Up pressed");
      PS4.setLed(0, 0, 255); // Blue
    }
    if (PS4.Down()) {
      Serial.println("Down pressed");
      PS4.setLed(255, 255, 0); // Yellow
    }
    if (PS4.Left()) {
      Serial.println("Left pressed");
      PS4.setLed(255, 0, 255); // Magenta
    }
    if (PS4.Right()) {
      Serial.println("Right pressed");
      PS4.setLed(0, 255, 255); // Cyan
    }
    
    // Face buttons
    if (PS4.Cross()) {
      Serial.println("Cross");
      PS4.setRumble(50, 100);
    }
    if (PS4.Circle()) {
      Serial.println("Circle");
      PS4.setRumble(100, 50);
    }
    if (PS4.Triangle()) {
      Serial.println("Triangle");
      PS4.setFlashRate(50, 50); // Flash LED
    }
    if (PS4.Square()) {
      Serial.println("Square");
      PS4.setFlashRate(0, 0); // Stop flashing
    }
    
    // Shoulder buttons
    if (PS4.L1()) {
      Serial.println("L1 pressed");
    }
    if (PS4.R1()) {
      Serial.println("R1 pressed");
    }
    if (PS4.L2()) {
      Serial.print("L2 pressed with value: ");
      Serial.println(PS4.L2Value());
    }
    if (PS4.R2()) {
      Serial.print("R2 pressed with value: ");
      Serial.println(PS4.R2Value());
    }
    
    // Analog sticks
    if (PS4.L3()) {
      Serial.println("L3 (Left stick button) pressed");
    }
    if (PS4.R3()) {
      Serial.println("R3 (Right stick button) pressed");
    }
    
    // Options and Share buttons
    if (PS4.Share()) {
      Serial.println("Share button pressed");
    }
    if (PS4.Options()) {
      Serial.println("Options button pressed");
    }
    
    // PS and Touchpad buttons
    if (PS4.PSButton()) {
      Serial.println("PS button pressed");
    }
    if (PS4.Touchpad()) {
      Serial.println("Touchpad pressed");
    }
    
    // Read analog stick values (-128 to 127)
    int8_t lx = PS4.LStickX();
    int8_t ly = PS4.LStickY();
    int8_t rx = PS4.RStickX();
    int8_t ry = PS4.RStickY();
    
    if (abs(lx) > 10 || abs(ly) > 10) {
      Serial.printf("Left Stick: X=%d, Y=%d\n", lx, ly);
    }
    
    if (abs(rx) > 10 || abs(ry) > 10) {
      Serial.printf("Right Stick: X=%d, Y=%d\n", rx, ry);
    }
    
    // Read sensor data
    Serial.printf("Accelerometer: X=%d, Y=%d, Z=%d\n", 
                  PS4.SensorX(), PS4.SensorY(), PS4.SensorZ());
    Serial.printf("Gyroscope Z: %d\n", PS4.GyroZ());
    
    // Read status
    Serial.printf("Battery: %d%%, Charging: %s\n", 
                  PS4.Battery(), PS4.Charging() ? "Yes" : "No");
    
    // Stop rumble after buttons are released
    if (!PS4.Cross() && !PS4.Circle()) {
      PS4.setRumble(0, 0);
    }
  }
  
  delay(50);
}
