#ifndef UTILS_H
#define UTILS_H

#include "global.h"

void freeBarang(Barang* b);
Status intToStatus(unsigned int pilihan);
unsigned int getOrAddLookupEntry(byte countAddr, int startAddr, int maxEntries, unsigned int baseId, const char* name);
int getID(const char* name, char selection);
bool getName(unsigned int searchId, char selection, char* outBuffer);
bool addBarangBackup(BarangBackup newItem);
bool saveToBackup(Barang activeItem);
void loadDatabaseToLinkedList();
void syncNodeToEEPROM(Node* updatedNode);
void syncDeleteToEEPROM(unsigned int targetId);

#endif