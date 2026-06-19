# ifndef LINKED_LIST_H
# define LINKED_LIST_H

#include "global.h"
typedef struct Node {
    Barang data;        // Data barang dengan struct Barang dari global.h
    int next;  
} Node;

void initSlot(int *head_index, bool slot_terpakai[]);
int getSlotKosong(bool slot_terpakai[]);
void addNodeToList(Barang newBarang, int* success, int *head_index, bool slot_terpakai[]);
void deleteNodeFromList(unsigned int targetId, int* success, int *head_index, bool slot_terpakai[]);
void removeList(int *head_index, bool slot_terpakai[]);

#endif