#include "linked_list.h"

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "utils.h"
#include "EEPROM.h"

void initSlot(int *head_index, bool slot_terpakai[]) {
    memset(slot_terpakai, false, sizeof(bool) * MAX_NODES);

    EEPROM.get(EEPROM_HEAD_ADDR, *head_index);

    if (*head_index < -1 || *head_index >= MAX_NODES) {
        *head_index = -1;
        EEPROM.put(EEPROM_HEAD_ADDR, *head_index);
    }

    int current = *head_index;
    int count = 0;
    while (current != -1 && count < MAX_NODES) {
        slot_terpakai[current] = true; // Tandai loker ini terpakai
        Node n = readNodeFromFlash(current);
        current = n.next;
        count++;
    }
    
    Serial.print("Sistem Siap. Jumlah barang tersimpan: ");
    Serial.println(count);
}

int getSlotKosong(bool slot_terpakai[]) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (!slot_terpakai[i]) {
            return i; 
        }
    }
    return -1;
}

void addNodeToList(Barang newBarang, int* success, int *head_index, bool slot_terpakai[]){
    *success = 0;

    int slot_baru = getSlotKosong(slot_terpakai);
    if (slot_baru == -1) {
        Serial.print("GAGAL: Penyimpanan Flash Penuh (");
        Serial.print(MAX_NODES);
        Serial.print("/");
        Serial.print(MAX_NODES);
        Serial.println(")");
        return;
    }

    Node nodeBaru;
    nodeBaru.data = newBarang;
    nodeBaru.next = *head_index;

    Serial.println(F("Breakpoint1.1"));
    Serial.flush();

    saveNodeToFlash(slot_baru, &nodeBaru);

    Serial.println(F("Breakpoint1.2"));
    Serial.flush();

    slot_terpakai[slot_baru] = true;
    *head_index = slot_baru;
    EEPROM.put(EEPROM_HEAD_ADDR, *head_index); 

    Serial.print("Berhasil menambah barang di slot: ");
    Serial.println(slot_baru);
    Serial.flush();
}

void deleteNodeFromList(unsigned int targetId, int* success, int *head_index, bool slot_terpakai[]){
    *success = 0;

    if (*head_index == -1) {
        Serial.println("GAGAL: List kosong, tidak ada yang bisa dihapus.");
        return;
    }

    int current_index = *head_index;
    int prev_index = -1;
    int count = 0;

    while (current_index != -1 && count < MAX_NODES) {
        Node currentNode = readNodeFromFlash(current_index);

        if (currentNode.data.id == targetId) {            
            if (prev_index == -1) {
                *head_index = currentNode.next;
                EEPROM.put(EEPROM_HEAD_ADDR, *head_index);
            } else {
                Node prevNode = readNodeFromFlash(prev_index);
                prevNode.next = currentNode.next;
                
                saveNodeToFlash(prev_index, &prevNode);
            }

            slot_terpakai[current_index] = false;

            Serial.print("Berhasil menghapus barang dengan ID: ");
            Serial.println(targetId);
            *success = 1;
            return;
        }

        // Lanjut ke node berikutnya
        prev_index = current_index;
        current_index = currentNode.next;
        count++;
    }

    Serial.print("GAGAL: Barang dengan ID ");
    Serial.print(targetId);
    Serial.println(" tidak ditemukan.");
    *success = 0;
    return;
}

void removeList(int *head_index, bool slot_terpakai[]) {
    *head_index = -1;
    
    EEPROM.put(EEPROM_HEAD_ADDR, *head_index);

    memset(slot_terpakai, false, sizeof(bool) * MAX_NODES);

    Serial.println(">> SEMUA DATA BERHASIL DIHAPUS (FORMAT SELESAI) <<\n");
}