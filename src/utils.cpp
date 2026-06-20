
#include <Arduino.h>
#include "global.h"
#include "linked_list.h"
#include "utils.h"
#include <EEPROM.h>

void freeBarang(Barang* b){
    if (b == NULL) return;
    free(b->nama);    b->nama    = NULL;
    free(b->pemilik); b->pemilik = NULL;
}

Status intToStatus(unsigned int pilihan){
    if (pilihan == 1){
        return TERSEDIA;
    } else if (pilihan == 2){
        return DIPINJAM;
    } else if (pilihan == 3){
        return RUSAK;
    } else if (pilihan == 4){
        return HABIS;
    } else{
        return TERSEDIA;}
}

unsigned int getOrAddLookupEntry(byte countAddr, int startAddr, int maxEntries, unsigned int baseId, const char* name){
    byte count = EEPROM.read(countAddr);
    if (count == 255) count = 0;

    unsigned int currentId;
    char tempName[MAX_NAME_LENGTH];

    for (int i = 0; i < count; i++) {
        int address = startAddr + (i * ENTRY_SIZE);

        EEPROM.get(address, currentId);

        EEPROM.get(address + sizeof(unsigned int), tempName);

        if (strcmp(tempName, name) == 0) {
            return currentId; 
        }
    }

    if (count >= maxEntries) {
        Serial.println("Error: Table is FULL!");
        return 0; 
    }

    unsigned int newId = baseId + count; 

    memset(tempName, 0, MAX_NAME_LENGTH);
    strncpy(tempName, name, MAX_NAME_LENGTH - 1);

    int writeAddress = startAddr + (count * ENTRY_SIZE);

    EEPROM.put(writeAddress, newId);
    EEPROM.put(writeAddress + sizeof(unsigned int), tempName);

    count++;
    EEPROM.write(countAddr, count);

    return newId;
}

int getID(const char* name, char selection) {
    if (selection == 'L') {
        return getOrAddLookupEntry(META_LOC_COUNT_ADDR, LOC_START_ADDR, MAX_LOCATIONS, 1000, name);
    } 
    else if (selection == 'P') {
        return getOrAddLookupEntry(META_PIC_COUNT_ADDR, PIC_START_ADDR, MAX_PICS, 2000, name);
    } 
    else {
        Serial.println("Error: Invalid selection! Use 'L' or 'P'.");
        return 0; 
    }
}

bool getName(unsigned int searchId, char selection, char* outBuffer){
    byte countAddr;
    int startAddr;

    if (selection == 'L') {
        countAddr = META_LOC_COUNT_ADDR;
        startAddr = LOC_START_ADDR;
    } else if (selection == 'P') {
        countAddr = META_PIC_COUNT_ADDR;
        startAddr = PIC_START_ADDR;
    } else {
        strcpy(outBuffer, "Error");
        return false;
    }

    byte count = EEPROM.read(countAddr);
    if (count == 255) count = 0;

    unsigned int currentId;
    
    char tempString[10]; 

    for (int i = 0; i < count; i++) {
        int address = startAddr + (i * 12); // 12 is the ENTRY_SIZE
        
        EEPROM.get(address, currentId);

        if (currentId == searchId) {
            
            EEPROM.get(address + sizeof(unsigned int), tempString);
            
            strcpy(outBuffer, tempString);
            
            return true; 
        }
    }
    
    strcpy(outBuffer, "Unknown");
    return false;
}

bool addBarangBackup(BarangBackup newItem) {
    byte itemCount = EEPROM.read(META_ITEM_COUNT_ADDR);
    if (itemCount == 255) itemCount = 0; // Handle brand new EEPROM

    if (itemCount >= MAX_ITEMS) {
        Serial.println("Error: Backup Storage is FULL (Max 50)!");
        return false;
    }

    int writeAddress = BACKUP_START_ADDR + (itemCount * sizeof(BarangBackup));
    
    EEPROM.put(writeAddress, newItem);

    itemCount++;
    EEPROM.write(META_ITEM_COUNT_ADDR, itemCount);

    return true;
}

bool saveToBackup(Barang activeItem){
    
    BarangBackup backupData;

    backupData.id       = activeItem.id;
    backupData.kategori = activeItem.kategori;
    backupData.stock    = activeItem.stock;
    backupData.lokasi   = activeItem.lokasi; // This is already the integer ID
    backupData.stat     = activeItem.stat;
    backupData.PIC      = activeItem.PIC;    // This is already the integer ID

    bool success = addBarangBackup(backupData);
    
    if (success) {
        Serial.println("Backup successful!");
    } else {
        Serial.println("Backup failed.");
    }
    
    return success;
}

void loadDatabaseToLinkedList(){
    byte itemCount = EEPROM.read(META_ITEM_COUNT_ADDR);
    if (itemCount == 255) itemCount = 0;

    BarangBackup tempBackup;

    Serial.print("Loading ");
    Serial.print(itemCount);
    Serial.println(" items into SRAM Linked List...");

    for (int i = 0; i < itemCount; i++) {
        int address = BACKUP_START_ADDR + (i * sizeof(BarangBackup));
        
        EEPROM.get(address, tempBackup);

        Node* newNode = new Node; 
        
        if (newNode == NULL) {
            Serial.println("CRITICAL ERROR: SRAM is full! Cannot load more items.");
            break; 
        }

        newNode->data.id       = tempBackup.id;
        newNode->data.kategori = tempBackup.kategori;
        newNode->data.stock    = tempBackup.stock;
        newNode->data.lokasi   = tempBackup.lokasi; // Int ID
        newNode->data.stat     = (Status)tempBackup.stat; // Cast int back to enum
        newNode->data.PIC      = tempBackup.PIC;    // Int ID

        newNode->data.nama    = NULL;     
        newNode->data.pemilik = NULL;  

        // 6. Insert the new node at the front of the Linked List
        newNode->next = head;
        head = newNode; 
    }

    Serial.println("Database successfully loaded!");
}

void syncNodeToEEPROM(Node* updatedNode){
    if (updatedNode == NULL) return;

    byte itemCount = EEPROM.read(META_ITEM_COUNT_ADDR);
    if (itemCount == 255) itemCount = 0;

    unsigned int targetId = updatedNode->data.id;
    unsigned int currentId;

    for (int i = 0; i < itemCount; i++) {
        int address = BACKUP_START_ADDR + (i * sizeof(BarangBackup));
        
        EEPROM.get(address, currentId);

        if (currentId == targetId) {
            BarangBackup updatedBackup;
            updatedBackup.id       = updatedNode->data.id;
            updatedBackup.kategori = updatedNode->data.kategori;
            updatedBackup.stock    = updatedNode->data.stock;
            updatedBackup.lokasi   = updatedNode->data.lokasi;
            updatedBackup.stat     = updatedNode->data.stat;
            updatedBackup.PIC      = updatedNode->data.PIC;

            EEPROM.put(address, updatedBackup);
            return;
        }
    }
    
    Serial.println(F("Warning: ID tidak ditemukan di EEPROM. Backup gagal."));
}

void syncDeleteToEEPROM(unsigned int targetId){
    byte itemCount = EEPROM.read(META_ITEM_COUNT_ADDR);
    if (itemCount == 255 || itemCount == 0) return; // Empty EEPROM

    int targetIndex = -1;
    BarangBackup tempItem;

    for (int i = 0; i < itemCount; i++) {
        int address = BACKUP_START_ADDR + (i * sizeof(BarangBackup));
        EEPROM.get(address, tempItem);
        
        if (tempItem.id == targetId) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) return; 
    for (int i = targetIndex; i < itemCount - 1; i++) {
        int sourceAddr = BACKUP_START_ADDR + ((i + 1) * sizeof(BarangBackup));
        int destAddr   = BACKUP_START_ADDR + (i * sizeof(BarangBackup));

        EEPROM.get(sourceAddr, tempItem);
        EEPROM.put(destAddr, tempItem);
    }

    itemCount--;
    EEPROM.write(META_ITEM_COUNT_ADDR, itemCount);
}