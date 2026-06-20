#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "linked_list.h"
#include "add.h"
#include "utils.h"

char* dupString(const char* src) {
    if (src == NULL) return NULL;
    char* dst= (char*)malloc(strlen(src) + 1);

    if (dst == NULL) return NULL;

    strcpy(dst, src);
    return dst;
}

void addItem(Node** head) {
    Serial.println();
    Serial.println(F("=== Tambah Barang ==="));

    const size_t BUF = MAX_NAME_LENGTH;
    char buf[BUF];

    Barang b;
    memset(&b, 0, sizeof(Barang));

    //ID
    Serial.print(F("ID Barang (angka): "));
    getIntInput(&b.id);
    Serial.println(b.id);

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
    Serial.println(b.nama);

    //Kategori
    Serial.println(F("Kategori (E=Elektronik, M=Mekanik, K=Kimia, L=Lainnya): "));
    getCharInput(&b.kategori);
    Serial.println(b.kategori);

    //Jumlah stok
    Serial.print(F("Jumlah Stok: "));
    getIntInput(&b.stock);
    Serial.println(b.stock);

    //Lokasi
    Serial.print(F("Lokasi Penyimpanan: "));
    getStringInput(buf, BUF);
    b.lokasi = getID(buf, 'L');
    if (b.lokasi == 0) {
        Serial.println(F("Gagal: memori tidak cukup (lokasi)."));
        freeBarang(&b);
        return;
    }
    Serial.println(buf);

    //Status
    Serial.println(F("Status (1=Tersedia, 2=Dipinjam, 3=Rusak, 4=Habis): "));
    unsigned int ps = 0;
    getIntInput(&ps);
    b.stat = intToStatus(ps);
    Serial.println(ps);

    //Pemilik
    Serial.print(F("Pemilik Barang: "));
    getStringInput(buf, BUF);
    b.pemilik = dupString(buf);
    if (b.pemilik == NULL) {
        Serial.println(F("Gagal: memori tidak cukup (pemilik)."));
        freeBarang(&b);
        return;
    }
    Serial.println(b.pemilik);
    //PIC
    Serial.print(F("PIC: "));
    getStringInput(buf, BUF);
    b.PIC = getID(buf, 'P');
    if (b.PIC == 0) {
        Serial.println(F("Gagal: memori tidak cukup (PIC)."));
        freeBarang(&b);
        return;
    }
    Serial.println(buf);

    //Masukkan ke linkedlist
    int success = 0;
    addNodeToList(head, b, &success);
    saveToBackup(b); // Simpan ke backup

    if (success == 1) {
        Serial.println(F("Barang berhasil ditambahkan."));
    } else {
        // Node malloc gagal; string yang sudah dialokasikan harus dibebaskan
        Serial.println(F("Gagal: tidak dapat mengalokasikan node (memori penuh)."));
        freeBarang(&b);
    }
}
