#include <arduino.h>
#include "search.h"
#include "linked_list.h"
#include "global.h"
#include "utils.h"

Node* searchListByID(unsigned int searchId){
    Node* current = head;

    while (current != NULL) {
        
        if (current->data.id == searchId) {
            return current; 
        }
        
        current = current->next;
    }
    
    return NULL; 
}

void searchListByName(const char* targetName){
    Node* current = head;
    bool foundAny = false;

    Serial.print(F("--- Searching for Name: '"));
    Serial.print(targetName);
    Serial.println(F("' ---"));

    while (current != NULL) {
        
        if (strcmp(current->data.nama, targetName) == 0) {
            
            Serial.print(F("- Found! ID: "));
            Serial.print(current->data.id);
            Serial.print(F(" | Stock: "));
            Serial.println(current->data.stock);
            
            foundAny = true;
        }
        
        current = current->next;
    }

    if (!foundAny) {
        Serial.println(F("No items matched that name."));
    }
    Serial.println(F("-----------------------------------"));
}
void searchItem(Node* head){
    Serial.println();
    Serial.println(F("=== Cari Barang Berdasarkan ID ==="));

    if (head == NULL) {
        Serial.println(F("Data inventaris kosong."));
        return;
    }

    Serial.print(F("Masukkan ID barang yang dicari: "));
    unsigned int targetId = 0;
    getIntInput(&targetId); 
    Serial.println(targetId); // Echo ID yang diketik user
    
    // Menggunakan helper function yang sudah Anda buat di search.cpp
    Node* current = searchListByID(targetId); 
    
    if (current != NULL) {
        char textBuffer[10]; // Buffer sementara untuk decode Lokasi & PIC
        
        Serial.print(F("--- Hasil Pencarian untuk ID '"));
        Serial.print(targetId);
        Serial.println(F("' ---"));

        Serial.print(F("  Nama     : ")); 
        Serial.println(current->data.nama);
        
        Serial.print(F("  ID       : ")); 
        Serial.println(current->data.id);
        
        Serial.print(F("  Kategori : ")); 
        Serial.println(current->data.kategori);
        
        Serial.print(F("  Stock    : ")); 
        Serial.println(current->data.stock);

        Serial.print(F("  Status   : "));
        switch(current->data.stat) {
            case TERSEDIA: Serial.println(F("Tersedia")); break;
            case DIPINJAM: Serial.println(F("Dipinjam")); break;
            case RUSAK:    Serial.println(F("Rusak")); break;
            case HABIS:    Serial.println(F("Habis")); break;
            default:       Serial.println(F("Unknown")); break;
        }

        Serial.print(F("  Lokasi   : "));
        if (getName(current->data.lokasi, 'L', textBuffer)) {
            Serial.println(textBuffer);
        } else {
            Serial.println(F("Unknown (ID tidak ditemukan)"));
        }

        Serial.print(F("  Pemilik  : ")); 
        Serial.println(current->data.pemilik);

        Serial.print(F("  PIC      : "));
        if (getName(current->data.PIC, 'P', textBuffer)) {
            Serial.println(textBuffer);
        } else {
            Serial.println(F("Unknown (ID tidak ditemukan)"));
        }

        Serial.println(F("-------------------------"));
    } else {
        Serial.println(F("Gagal: Barang dengan ID tersebut tidak ditemukan."));
        Serial.println(F("-------------------------"));
    }
}