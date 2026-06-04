#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once

#include <stdint.h>
#include <Arduino.h>

typedef enum SystemState : uint8_t {
    TERSEDIA,
    DIPINJAM,
    RUSAK,
    HABIS
} Status;


typedef struct{
    unsigned int id;    // Id barang dalam bentuk integer 
    char *nama;         // Nama barang dalam dynaamic array string
    char kategori;      // Kategori barang menggunakan 1 char
    unsigned int stock; // Sisa stock barang yang tersedia (maks 65,535)
    char *lokasi;       // Nama lokasi barang dalam dynamic array string
    Status stat;        // Status barang menggunakan enum untuk readability program
    char *pemilik;      // Nama pemilik barang dalam dynamic array string
    char *PIC;          // Nama PIC barang dalam dynamic array string
} Barang;



#endif