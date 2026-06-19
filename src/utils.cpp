
#include <Arduino.h>
#include "global.h"
#include "linked_list.h"
#include "utils.h"

void freeBarang(Barang* b) {
    if (b == NULL) return;
    free(b->nama);    b->nama    = NULL;
    free(b->lokasi);  b->lokasi  = NULL;
    free(b->pemilik); b->pemilik = NULL;
    free(b->PIC);     b->PIC     = NULL;
}

Status intToStatus(unsigned int pilihan) {
    if (pilihan == 1) {
        return TERSEDIA;
    } else if (pilihan == 2) {
        return DIPINJAM;
    } else if (pilihan == 3) {
        return RUSAK;
    } else if (pilihan == 4) {
        return HABIS;
    } else {
        return TERSEDIA;}
}