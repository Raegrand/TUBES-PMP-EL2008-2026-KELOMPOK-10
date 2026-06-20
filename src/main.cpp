#include "master_header.h"

int success = 1;
Node* head = NULL;

void setup() {
  Serial.begin(9600);
  delay(100);
  initList(&head);
  loadDatabaseToLinkedList();
  
  Serial.println(F("Arduino is ready! Type something and press enter:"));
}

void loop() {
    tampilkanMenu();

    unsigned int pilihan = 0;
    getIntInput(&pilihan); 
    Serial.println(pilihan); 
    switch (pilihan) {
        case 1:
            tampilkanSemuaBarang(head);
            break;
            
        case 2:
            addItem(&head); 
            break;
            
        case 3:
            updateStock(head);
            break;
            
        case 4:
            updateStatus(head);
            break;
            
        case 5:
            deleteItem(&head);
            break;

        case 6:
            searchItemByName(head);
            break;
            
        default:
            Serial.println(F("Gagal: Pilihan tidak valid. Silakan ketik angka 1-5."));
            break;
    }
    
    // Opsional: Berikan sedikit jeda sebelum menu muncul kembali
    delay(500); 
}