#include <Arduino.h>
#include "../header/ardu.h"

extern "C" {
    // 1. A function to set up the hardware
    void init_hardware(void) {
        init(); // Required when overriding main() on Arduino
        Serial.begin(9600);
    }

    // 2. The print wrappers
    void c_print(const char* text) {
        Serial.print(text);
    }

    void c_println(const char* text) {
        Serial.println(text);
    }
}