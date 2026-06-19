#include <Arduino.h>
#include "global.h"
#include "linked_list.h"
#include "remove.h"

void deleteItem(int *head_index, bool slot_terpakai[]) {
    Serial.println();
    Serial.println(F("=== Hapus Barang ==="));

    // Pengecekan list kosong menggunakan variabel global
    // (Pastikan Anda sudah menambahkan 'extern int head_index;' di file header Anda)
    if (*head_index == -1) {
        Serial.println(F("Data inventaris kosong."));
        return;
    }

    Serial.print(F("Masukkan ID barang yang akan dihapus: "));
    unsigned int targetId = 0;
    getIntInput(&targetId);

    // Panggil fungsi Flash Memory yang sudah kita buat sebelumnya
    int success = 0;
    deleteNodeFromList(targetId, &success, head_index, slot_terpakai);

    if (success == 1) {
        Serial.println(F("Barang berhasil dihapus secara logis dari Flash."));
    } else {
        // Jika hapusBarang mengembalikan false (ID tidak ketemu)
        Serial.println(F("Gagal: ID barang tidak ditemukan."));
    }
}
