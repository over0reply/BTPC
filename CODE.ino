#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX, TX for Bluetooth

void setup() {
  Serial.begin(9600);   // Communication with PC
  BTSerial.begin(9600); // Communication with Bluetooth module
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    BTSerial.println(command);  // Send command to Bluetooth module
  }
  if (BTSerial.available()) {
    String response = BTSerial.readStringUntil('\n');
    Serial.println(response);   // Send response to PC
  }
}
