
#include <Arduino.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "EEPROM.h"
#include "global.h"
#include "linked_list.h"
#include "utils.h"


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

void saveNodeToFlash(int node_index, Node* newNodeData) {
    if (node_index < 0 || node_index >= MAX_NODES) return; 

    uint32_t absolute_address = FLASH_BASE_ADDRESS + (node_index * sizeof(Node));
    uint32_t page_address = absolute_address & ~(SPM_PAGESIZE - 1);
    uint16_t offset_in_page = absolute_address % SPM_PAGESIZE;

    uint8_t ram_buffer[SPM_PAGESIZE];
    for (uint16_t i = 0; i < SPM_PAGESIZE; i++) {
        ram_buffer[i] = pgm_read_byte(page_address + i);
    }

    memcpy(&ram_buffer[offset_in_page], newNodeData, sizeof(Node));

    Serial.println(F("Breakpoint2.1"));
    Serial.flush();

    uint8_t sreg_backup = SREG; 
    cli(); 

    boot_page_erase(page_address);
    boot_spm_busy_wait(); 

    for (uint16_t i = 0; i < SPM_PAGESIZE; i += 2) {
        uint16_t word_data = ram_buffer[i] | (ram_buffer[i + 1] << 8);
        boot_page_fill(page_address + i, word_data);
    }

    
    boot_page_write(page_address);
    boot_spm_busy_wait(); 
    boot_rww_enable();
    SREG = sreg_backup; 
    delay(100);
    Serial.println(F("Breakpoint2.2"));
    Serial.flush();
}

Node readNodeFromFlash(int node_index) {
    Node tempNode;
    if (node_index < 0 || node_index >= MAX_NODES) {
        memset(&tempNode, 0, sizeof(Node));
        tempNode.next = -1; 
        return tempNode;
    }
    uint32_t absolute_address = FLASH_BASE_ADDRESS + (node_index * sizeof(Node));
    memcpy_P(&tempNode, (const void*)absolute_address, sizeof(Node));
    return tempNode;
}

void printSemuaNode(int head_index) {
    int current_index = head_index;
    int count = 0; 

    Serial.println(F("\n========== DAFTAR BARANG =========="));
    
    while (current_index != -1 && count < MAX_NODES) {
        Node currentNode = readNodeFromFlash(current_index);
        
        Serial.print(F("Lokasi Index : ")); Serial.println(current_index);
        Serial.print(F("ID Barang    : ")); Serial.println(currentNode.data.id);
        Serial.print(F("Nama Barang  : ")); Serial.println(currentNode.data.nama);
        Serial.print(F("Kategori     : ")); Serial.println(currentNode.data.kategori);
        Serial.print(F("Stock        : ")); Serial.println(currentNode.data.stock);
        Serial.print(F("Lokasi       : ")); Serial.println(currentNode.data.lokasi);
        Serial.print(F("Pemilik      : ")); Serial.println(currentNode.data.pemilik);
        Serial.print(F("PIC          : ")); Serial.println(currentNode.data.PIC);
        Serial.print(F("Next Index   : ")); Serial.println(currentNode.next);
        Serial.println(F("-----------------------------------"));
        
        // Lompat ke index node berikutnya
        current_index = currentNode.next;
        count++;
    }

    if (current_index == -1) {
        Serial.println(F(">> Akhir dari Linked List dicapai.\n"));
    } else {
        Serial.println(F(">> ERROR: Loop berulang terdeteksi di Flash Memory!\n"));
    }
}