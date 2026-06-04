#include "global.h"
#include <stdlib.h>

// Membaca input teks dari pengguna dan mencegah overflow pada buffer
void getStringInput(char* buffer, size_t bufferSize){
    size_t index = 0;
    while (index < bufferSize - 1) { 
        if (Serial.available() > 0) {
            char incomingByte = Serial.read();
            if (incomingByte == '\n' || incomingByte == '\r') { 
                if (index > 0) {
                    break;
                }
                else {
                    continue; 
                }
            }
            buffer[index++] = incomingByte;
        }
    }
    buffer[index] = '\0'; 
}

// Membaca input berupa angka bulat positif (unsigned integer)
void getIntInput(unsigned int* value){
    char inputBuffer[20]; 
    getStringInput(inputBuffer, sizeof(inputBuffer));
    *value = static_cast<unsigned int>(strtoul(inputBuffer, nullptr, 10));
}

// Membaca input berupa karakter tunggal (char)
void getCharInput(char* value){
    char inputBuffer[2]; 
    getStringInput(inputBuffer, sizeof(inputBuffer));
    *value = inputBuffer[0];
}