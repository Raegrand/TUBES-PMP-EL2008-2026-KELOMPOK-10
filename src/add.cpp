#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "linked_list.h"
#include "add.h"
#include "utils.h"

void addItem(Node** head) {
    Serial.println();
    Serial.println(F("=== Tambah Barang ==="));

    const size_t BUF = 64;
    char buf[BUF];

    Barang b;
    memset(&b, 0, sizeof(Barang));

    //ID
    Serial.print(F("ID Barang (angka): "));
    getIntInput(&b.id);

    // Cek duplikat ID terlebih dahulu sebelum mengalokasikan heap apapun
    Node* existing = NULL;
    findNodeById(*head, b.id, &existing);
    if (existing != NULL) {
        Serial.println(F("Gagal: ID sudah terdaftar. Gunakan ID lain."));
        return;
    }

    // Nama
    Serial.print(F("Nama Barang: "));
    getStringInput(buf, BUF);
    b.nama = dupString(buf);
    if (b.nama == NULL) {
        Serial.println(F("Gagal: memori tidak cukup (nama)."));
        freeBarang(&b);
        return;
    }

    //Kategori
    Serial.println(F("Kategori (E=Elektronik, M=Mekanik, K=Kimia, L=Lainnya): "));
    getCharInput(&b.kategori);

    //Jumlah stok
    Serial.print(F("Jumlah Stok: "));
    getIntInput(&b.stock);

    //Lokasi
    Serial.print(F("Lokasi Penyimpanan: "));
    getStringInput(buf, BUF);
    b.lokasi = dupString(buf);
    if (b.lokasi == NULL) {
        Serial.println(F("Gagal: memori tidak cukup (lokasi)."));
        freeBarang(&b);
        return;
    }

    //Status
    Serial.println(F("Status (1=Tersedia, 2=Dipinjam, 3=Rusak, 4=Habis): "));
    unsigned int ps = 0;
    getIntInput(&ps);
    b.stat = intToStatus(ps);

    //Pemilik
    Serial.print(F("Pemilik Barang: "));
    getStringInput(buf, BUF);
    b.pemilik = dupString(buf);
    if (b.pemilik == NULL) {
        Serial.println(F("Gagal: memori tidak cukup (pemilik)."));
        freeBarang(&b);
        return;
    }

    //PIC
    getStringInput(buf, BUF);
    b.PIC = dupString(buf);
    if (b.PIC == NULL) {
        Serial.println(F("Gagal: memori tidak cukup (PIC)."));
        freeBarang(&b);
        return;
    }

    //Masukkan ke linkedlist
    int success = 0;
    addNodeToList(head, b, &success);

    if (success == 1) {
        Serial.println(F("Barang berhasil ditambahkan."));
    } else {
        // Node malloc gagal; string yang sudah dialokasikan harus dibebaskan
        Serial.println(F("Gagal: tidak dapat mengalokasikan node (memori penuh)."));
        freeBarang(&b);
    }
}
