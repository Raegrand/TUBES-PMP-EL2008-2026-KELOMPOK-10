#include "interface.h"
#include "global.h"
#include "linked_list.h"
#include "utils.h"

void tampilkanSemuaBarang(Node* head){
    Serial.println();
    Serial.println(F("========================================="));
    Serial.println(F("         DAFTAR INVENTARIS BARANG        "));
    Serial.println(F("========================================="));

    if (head == NULL) {
        Serial.println(F("Data inventaris kosong. Belum ada barang."));
        Serial.println(F("========================================="));
        return;
    }

    Node* current = head;
    char textBuffer[10]; // Buffer sementara untuk decode string Lokasi & PIC
    int count = 1;

    while (current != NULL) {
        Serial.print(F("Barang #")); 
        Serial.println(count);
        
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

        Serial.println(F("-----------------------------------------"));
        
        current = current->next;
        count++;
    }
    
    Serial.print(F("Total Item Unik: "));
    Serial.println(count - 1);
    Serial.println(F("========================================="));
}

void tampilkanMenu(){
    Serial.println();
    Serial.println(F("========================================="));
    Serial.println(F("       SISTEM INVENTARIS GUDANG          "));
    Serial.println(F("========================================="));
    Serial.println(F("1. Tampilkan Semua Barang"));
    Serial.println(F("2. Tambah Barang Baru"));
    Serial.println(F("3. Update Stok Barang"));
    Serial.println(F("4. Update Status Barang"));
    Serial.println(F("5. Hapus Barang"));
    Serial.println(F("6. Cari Barang"));
    Serial.println(F("========================================="));
    Serial.print(F("Masukkan pilihan Anda (1-6): "));
}