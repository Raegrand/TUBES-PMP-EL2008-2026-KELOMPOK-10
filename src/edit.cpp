#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "linked_list.h"
#include "add.h"
#include "utils.h"

void updateStock(Node* head) {
    Serial.println();
    Serial.println(F("=== Update Stok ==="));

    if (head == NULL) {
        Serial.println(F("Data inventaris kosong."));
        return;
    }

    Serial.print(F("Masukkan ID barang: "));
    unsigned int targetId = 0;
    getIntInput(&targetId);

    Node* result = NULL;
    findNodeById(head, targetId, &result);

    if (result == NULL) {
        Serial.println(F("Gagal: ID barang tidak ditemukan."));
        return;
    }

    // Tampilkan stok saat ini sebagai referensi user
    Serial.print(F("Stok saat ini: "));
    Serial.println(result->data.stock);

    Serial.print(F("Masukkan stok baru: "));
    getIntInput(&result->data.stock);

    // Aturan bisnis: stok 0 → HABIS otomatis
    if (result->data.stock == 0) {
        result->data.stat = HABIS;
        Serial.println(F("Info: Status diubah ke 'Habis' karena stok = 0."));
    }

    Serial.println(F("Stok berhasil diperbarui."));
}

void updateStatus(Node* head) {
    Serial.println();
    Serial.println(F("=== Update Status ==="));

    if (head == NULL) {
        Serial.println(F("Data inventaris kosong."));
        return;
    }

    Serial.print(F("Masukkan ID barang: "));
    unsigned int targetId = 0;
    getIntInput(&targetId);

    Node* result = NULL;
    findNodeById(head, targetId, &result);

    if (result == NULL) {
        Serial.println(F("Gagal: ID barang tidak ditemukan."));
        return;
    }

    Serial.println(F("Status baru (1=Tersedia, 2=Dipinjam, 3=Rusak, 4=Habis): "));
    unsigned int ps = 0;
    getIntInput(&ps);
    result->data.stat = intToStatus(ps);

    Serial.println(F("Status berhasil diperbarui."));
}
