#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);
  
  // Initialize PS4 controller
  // Optional: Set a specific MAC address for pairing
  // PS4.begin("01:02:03:04:05:06");
  PS4.begin();
  
  Serial.println("PS4 Controller initialized");
  Serial.println("Waiting for PS4 controller to connect...");
}

void loop() {
  // Check if controller is connected
  if (PS4.isConnected()) {
    // Read button states
    if (PS4.Cross()) {
      Serial.println("Cross button pressed");
    }
    
    if (PS4.Circle()) {
      Serial.println("Circle button pressed");
    }
    
    if (PS4.Triangle()) {
      Serial.println("Triangle button pressed");
    }
    
    if (PS4.Square()) {
      Serial.println("Square button pressed");
    }
    
    if (PS4.PSButton()) {
      Serial.println("PS button pressed");
    }
    
    // Read analog stick values
    if (PS4.LStickX() != 0 || PS4.LStickY() != 0) {
      Serial.print("Left Stick: X=");
      Serial.print(PS4.LStickX());
      Serial.print(", Y=");
      Serial.println(PS4.LStickY());
    }
    
    if (PS4.RStickX() != 0 || PS4.RStickY() != 0) {
      Serial.print("Right Stick: X=");
      Serial.print(PS4.RStickX());
      Serial.print(", Y=");
      Serial.println(PS4.RStickY());
    }
    
    // Read trigger values
    if (PS4.L2Value() > 0) {
      Serial.print("L2 Trigger: ");
      Serial.println(PS4.L2Value());
    }
    
    if (PS4.R2Value() > 0) {
      Serial.print("R2 Trigger: ");
      Serial.println(PS4.R2Value());
    }
    
    // Read battery level
    Serial.print("Battery: ");
    Serial.print(PS4.Battery());
    Serial.println("%");
    
    // Set LED color (red, green, blue)
    PS4.setLed(255, 0, 0);
    
    // Set rumble (small rumble, large rumble)
    if (PS4.Cross()) {
      PS4.setRumble(100, 200);
      delay(200);
      PS4.setRumble(0, 0);
    }
  }
  
  delay(100);
}
