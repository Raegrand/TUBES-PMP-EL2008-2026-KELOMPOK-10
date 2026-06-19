#include "master_header.h"

int success = 0;
bool slot_terpakai[MAX_NODES];
int head_index = -1;

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println(F("Arduino is ready! Type something and press enter:"));
  Serial.flush();
}

void loop() {
  initSlot(&head_index, slot_terpakai);
  delay(200);
  if(success == 0){
    for(int i = 1; i < 10000; i++){//memory full tester
      Serial.print(F("Adding item with ID: "));
      Serial.println(i);
      Barang b;
      b.id = i;
      strcpy(b.nama, "BarangTest");
      b.kategori = 'E';
      b.stock = 10;
      strcpy(b.lokasi, "R");
      b.stat = TERSEDIA;
      strcpy(b.PIC, "PICTest");
      delay(500);
      addNodeToList(b, &success, &head_index, slot_terpakai);
    }
  }
  else{
    Serial.println(F("Memory is full, cannot add more items."));
  }
  delay(200);
}