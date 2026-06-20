#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once

#include <stdint.h>
#include <Arduino.h>

#define MAX_NAME_LENGTH 10

// EEPROM Address Map:
#define META_ITEM_COUNT_ADDR 0   // Current count of BarangBackup items
#define META_LOC_COUNT_ADDR  1   // Current count of Locations
#define META_PIC_COUNT_ADDR  2   // Current count of PICs

// --- 1. LOCATIONS (Addresses 10 - 129) ---
// Capacity: 10 entries (12 bytes per entry)
#define LOC_START_ADDR 10
#define MAX_LOCATIONS  10

// --- 2. PICs (Addresses 130 - 249) ---
// Capacity: 10 entries (12 bytes per entry)
#define PIC_START_ADDR 130
#define MAX_PICS       10

// --- 3. BACKUP ITEMS (Addresses 250 - 849) ---
// Capacity: 50 entries (12 bytes per entry)
#define BACKUP_START_ADDR 250
#define MAX_ITEMS         50

#define ENTRY_SIZE        12

typedef enum SystemState : uint8_t {
    TERSEDIA,   // Barang ada dan siap dipinjam
    DIPINJAM,   // Barang sedang dipakai/dipinjam orang lain
    RUSAK,      // Barang dalam kondisi tidak bisa digunakan
    HABIS       // Stok barang sedang kosong
} Status;


typedef struct{
    unsigned int id;    // Id barang dalam bentuk integer 
    char* nama;         // Nama barang dalam dynaamic array string
    char kategori;      // Kategori barang menggunakan 1 char
    unsigned int stock; // Sisa stock barang yang tersedia (maks 65,535)
    unsigned int lokasi;       // Nama lokasi barang dalam dynamic array string
    Status stat;        // Status barang menggunakan enum untuk readability program
    char* pemilik;      // Nama pemilik barang dalam dynamic array string
    unsigned int PIC;          // Nama PIC barang dalam dynamic array string
} Barang;

typedef struct{
    unsigned int id;    // Id barang dalam bentuk integer 
    char kategori;      // Kategori barang menggunakan 1 char
    unsigned int stock; // Sisa stock barang yang tersedia (maks 65,535)
    unsigned int lokasi;       // Nama lokasi barang dalam dynamic array string
    Status stat;        // Status barang menggunakan enum untuk readability program
    unsigned int PIC;          // Nama PIC barang dalam dynamic array string
} BarangBackup;


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