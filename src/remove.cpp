#include <Arduino.h>
#include "global.h"
#include "linked_list.h"
#include "remove.h"

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

    int success= 0;
    deleteNodeFromList(head, targetId, &success);

    if (success == 1) {
        Serial.println(F("Barang berhasil dihapus."));
    } else {
        Serial.println(F("Gagal: ID barang tidak ditemukan."));
    }
}
