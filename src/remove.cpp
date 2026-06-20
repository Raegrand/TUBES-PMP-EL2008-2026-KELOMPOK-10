#include <Arduino.h>
#include "global.h"
#include "linked_list.h"
#include "remove.h"
#include "utils.h"
#include "EEPROM.h"

void deleteItem(Node** head) {
    Serial.println();
    Serial.println(F("=== Hapus Barang ==="));

    if (head == NULL || *head == NULL) {
        Serial.println(F("Data inventaris kosong."));
        return;
    }

    Serial.print(F("Masukkan ID barang yang akan dihapus: "));
    unsigned int targetId = 0;
    getIntInput(&targetId);
    Serial.println(targetId);
    int success= 0;
    deleteNodeFromList(head, targetId, &success);

    if (success == 1) {
        syncDeleteToEEPROM(targetId);
        Serial.println(F("Barang berhasil dihapus."));
    } else {
        Serial.println(F("Gagal: ID barang tidak ditemukan."));
    }
}

void deleteAllItems(Node** head) {
    Serial.println();
    Serial.println(F("=== Hapus Semua Barang (WIPE DATA) ==="));

    if (head == NULL || *head == NULL) {
        Serial.println(F("Data inventaris sudah kosong."));
        return;
    }

    Serial.println(F("PERINGATAN BAHAYA: Anda yakin ingin menghapus SEMUA barang?"));
    Serial.print(F("Ketik '1' untuk YA (Hapus), atau angka lain untuk BATAL: "));
    
    unsigned int konfirmasi = 0;
    getIntInput(&konfirmasi);
    Serial.println(konfirmasi); // Echo pilihan user

    if (konfirmasi == 1) {
        
        freeAllNodes(head);

        EEPROM.write(META_ITEM_COUNT_ADDR, 0);

        Serial.println(F("Berhasil: Seluruh barang telah dihapus dari SRAM dan EEPROM."));
        
    } else {
        Serial.println(F("Aman: Proses hapus semua barang DIBATALKAN."));
    }
}