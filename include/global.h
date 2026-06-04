#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once

#include <stdint.h>
#include <Arduino.h>

typedef enum SystemState : uint8_t {
    TERSEDIA,   // Barang ada dan siap dipinjam
    DIPINJAM,   // Barang sedang dipakai/dipinjam orang lain
    RUSAK,      // Barang dalam kondisi tidak bisa digunakan
    HABIS       // Stok barang sedang kosong
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

// ============================================================================
// DEKLARASI FUNGSI (I/O)
// ============================================================================

// Membaca input teks dari pengguna dan mencegah overflow pada buffer
void getStringInput(char* buffer, size_t bufferSize);

// Membaca input berupa angka bulat positif (unsigned integer)
void getIntInput(unsigned int* value);

// Membaca input berupa karakter tunggal (char)
void getCharInput(char* value);

#endif