# ifndef LINKED_LIST_H
# define LINKED_LIST_H

#include "global.h"
typedef struct Node {
    Barang data;        // Data barang dengan struct Barang dari global.h
    struct Node* next;  
} Node;
extern Node* head;

void initList(Node** head);
void addNodeToList(Node** head, Barang newBarang, int* success);
void deleteNodeFromList(Node** head, unsigned int targetId, int* success);
void findNodeById(Node* head, unsigned int targetId, Node** result);
void countNodes(Node* head, int* count);
void freeAllNodes (Node**head);

#endif