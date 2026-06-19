#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "linked_list.h"
#include "add.h"
#include "utils.h"

void updateStock(int *head_index, bool slot_terpakai[]) {
    Serial.println();
    Serial.println(F("=== Update Stok ==="));

    // Gunakan variabel global head_index, bukan parameter
    if (*head_index == -1) {
        Serial.println(F("Data inventaris kosong."));
        return;
    }

    Serial.print(F("Masukkan ID barang: "));
    unsigned int targetId = 0;
    getIntInput(&targetId);

    // 1. Cari node dan catat indeksnya
    int current_index = *head_index;
    Node targetNode;
    bool found = false;

    while (current_index != -1) {
        targetNode = readNodeFromFlash(current_index);
        if (targetNode.data.id == targetId) {
            found = true;
            break; // Berhenti mencari, current_index sekarang menyimpan posisi yang benar
        }
        current_index = targetNode.next;
    }

    if (!found) {
        Serial.println(F("Gagal: ID barang tidak ditemukan."));
        return;
    }

    // 2. Tampilkan stok saat ini sebagai referensi user
    Serial.print(F("Stok saat ini: "));
    Serial.println(targetNode.data.stock);

    // 3. Minta input stok baru
    Serial.print(F("Masukkan stok baru: "));
    getIntInput(&targetNode.data.stock);

    // Aturan bisnis: stok 0 → HABIS otomatis
    if (targetNode.data.stock == 0) {
        targetNode.data.stat = HABIS; // Pastikan HABIS ada di enum Status Anda!
        Serial.println(F("Info: Status diubah ke 'Habis' karena stok = 0."));
    }

    // 4. SIMPAN KEMBALI KE FLASH MEMORY
    saveNodeToFlash(current_index, &targetNode);

    Serial.println(F("Stok berhasil diperbarui."));
}

void updateStatus(int *head_index, bool slot_terpakai[]) {
    Serial.println();
    Serial.println(F("=== Update Status ==="));

    if (*head_index == -1) {
        Serial.println(F("Data inventaris kosong."));
        return;
    }

    Serial.print(F("Masukkan ID barang: "));
    unsigned int targetId = 0;
    getIntInput(&targetId);

    // 1. Cari node dan catat indeksnya
    int current_index = *head_index;
    Node targetNode;
    bool found = false;

    while (current_index != -1) {
        targetNode = readNodeFromFlash(current_index);
        if (targetNode.data.id == targetId) {
            found = true;
            break;
        }
        current_index = targetNode.next;
    }

    if (!found) {
        Serial.println(F("Gagal: ID barang tidak ditemukan."));
        return;
    }

    // 2. Minta status baru
    Serial.println(F("Status baru (1=Tersedia, 2=Dipinjam, 3=Rusak, 4=Habis): "));
    unsigned int ps = 0;
    getIntInput(&ps);
    
    // Asumsi fungsi intToStatus mengubah angka jadi Enum
    targetNode.data.stat = intToStatus(ps); 

    // 3. SIMPAN KEMBALI KE FLASH MEMORY
    saveNodeToFlash(current_index, &targetNode);

    Serial.println(F("Status berhasil diperbarui."));
}