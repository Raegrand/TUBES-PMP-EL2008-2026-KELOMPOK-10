#include "master_header.h"

int success = 1;
Node* head = NULL;

void setup() {
  Serial.begin(9600);
  delay(100);
  initList(&head);
  loadDatabaseToLinkedList();
  Barang temp;
  if(success == 1){
    for(int i = 0; i < 45; i++) {
      Serial.print(F("Adding item with ID: "));
      Serial.println(i);
      temp.id = i;
      temp.nama = dupString("Test");
      temp.kategori = 'E';
      temp.stock = 10;
      temp.lokasi = getID("Test", 'L');
      temp.stat = TERSEDIA;
      temp.pemilik = dupString("Test");
      temp.PIC = getID("Test", 'P');
      addNodeToList(&head, temp, &success);
      saveToBackup(temp);
      if(success == 0){
        Serial.print(F("Memory allocation failed at iteration: "));
        Serial.println(i);
        break;
      }
    } 
  }
  Serial.println(F("Arduino is ready! Type something and press enter:"));
}

void loop() {
  delay(200);
}