#include "linked_list.h"

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "utils.h"

void initList(Node** head) {
    if (head == NULL) return;
    *head = NULL;
}

void addNodeToList(Node** head, Barang newBarang, int* success) {
    *success = 0;

    if (head == NULL) return;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return;    
    newNode->data = newBarang;      
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        *success = 1;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    *success = 1;
}

void deleteNodeFromList(Node** head, unsigned int targetId, int* success) {
    *success = 0;

    if (head == NULL || *head == NULL) return;

    Node* temp = *head;
    Node* prev = NULL;

    // Traverse sambil mencari ID yang cocok
    while (temp != NULL) {
        if (temp->data.id == targetId) {

            
            if (prev== NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }

            freeBarang(&temp->data);
            free(temp);

            *success = 1;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void findNodeById(Node* head, unsigned int targetId, Node** result) {
    *result = NULL;

    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.id == targetId) {
            *result = temp;
            return;
        }
        temp = temp->next;
    }
}


void countNodes(Node* head, int* count) {
    *count = 0;
    Node* temp = head;
    while (temp != NULL) {
        (*count)++;
        temp = temp->next;
    }
}


void freeAllNodes(Node** head) {
    if (head == NULL) return;

    Node* temp = *head;
    Node* next = NULL;

    while (temp != NULL) {
        next = temp->next;          
        freeBarang(&temp->data);
        free(temp);
        temp = next;
    }

    *head = NULL;
}
