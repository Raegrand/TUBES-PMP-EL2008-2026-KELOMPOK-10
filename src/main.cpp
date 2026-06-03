#include "master_header.h"

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Arduino is ready! Type something and press enter:");
}

void loop() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    
    // Read the incoming byte
    char incomingChar = Serial.read();
    
    // Ignore the hidden 'newline' characters when you press enter
    if (incomingChar != '\n' && incomingChar != '\r') {
      Serial.print("I received: ");
      Serial.println(incomingChar);
    }
  }
}