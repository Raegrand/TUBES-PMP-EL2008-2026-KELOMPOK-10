#include "master_header.h"

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println(F("Arduino is ready! Type something and press enter:"));
}

void loop() {
  char a;
  getCharInput(&a);
  Serial.print(F("You entered: "));
  Serial.println(a);
}