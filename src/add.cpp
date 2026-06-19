#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "linked_list.h"
#include "add.h"
#include "utils.h"

void addItem(int *head_index, bool slot_terpakai[]) {
    Serial.println();
    Serial.println(F("=== Tambah Barang ==="));

    // Membuat struct Barang lokal dan mengosongkan datanya
    Barang b;
    memset(&b, 0, sizeof(Barang));

    // ID   
    Serial.print(F("ID Barang (angka): "));
    getIntInput(&b.id);

    // // Cek duplikat ID di Flash Memory
    // Node cekNode = findNodeById(b.id);
    // if (cekNode.data.id != 0) { // Jika ID tidak 0, berarti barang dengan ID tersebut sudah ada
    //     Serial.println(F("Gagal: ID sudah terdaftar. Gunakan ID lain."));
    //     return;
    // }

    // Nama
    Serial.print(F("Nama Barang: "));
    // Menggunakan sizeof(b.nama) agar otomatis menyesuaikan dengan batas 16 karakter
    getStringInput(b.nama, sizeof(b.nama)); 
    if (strlen(b.nama) == 0) {
        Serial.println(F("Gagal: nama tidak boleh kosong."));
        return;
    }

    // Kategori
    Serial.println(F("Kategori (E=Elektronik, M=Mekanik, K=Kimia, L=Lainnya): "));
    getCharInput(&b.kategori);

    // Jumlah stok
    Serial.print(F("Jumlah Stok: "));
    getIntInput(&b.stock);

    // Lokasi
    Serial.print(F("Lokasi Penyimpanan: "));
    // Menggunakan sizeof(b.lokasi) yang berukuran 8 karakter
    getStringInput(b.lokasi, sizeof(b.lokasi)); 
    if (strlen(b.lokasi) == 0) {
        Serial.println(F("Gagal: lokasi tidak boleh kosong."));
        return;
    }

    // Status
    Serial.println(F("Status (1=Tersedia, 2=Dipinjam, 3=Rusak, 4=Habis): "));
    unsigned int ps = 0;
    getIntInput(&ps);
    b.stat = intToStatus(ps); // Asumsi fungsi ini ada di utils.h untuk konversi ke Enum

    // Pemilik
    Serial.print(F("Pemilik Barang: "));
    getStringInput(b.pemilik, sizeof(b.pemilik));
    if (strlen(b.pemilik) == 0) {
        Serial.println(F("Gagal: pemilik tidak boleh kosong."));
        return;
    }

    // PIC
    Serial.print(F("Nama PIC: ")); // Ditambahkan baris Serial.print yang tadinya tertinggal
    getStringInput(b.PIC, sizeof(b.PIC));
    if (strlen(b.PIC) == 0) {
        Serial.println(F("Gagal: PIC tidak boleh kosong."));
        return;
    }

    // Masukkan ke Flash Memory menggunakan fungsi yang sudah kita buat
    int success = 0;
    addNodeToList(b, &success, head_index, slot_terpakai);

    if (success == 1) {
        Serial.println(F("Barang berhasil ditambahkan ke memori Flash."));
    } else {
        Serial.println(F("Gagal: Kapasitas memori Flash (200 Slot) sudah penuh."));
    }
}
