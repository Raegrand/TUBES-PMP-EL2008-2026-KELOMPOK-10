#include <arduino.h>
#include "search.h"
#include "linked_list.h"
#include "global.h"
#include "utils.h"

Node* searchListByID(unsigned int searchId){
    Node* current = head;

    while (current != NULL) {
        
        if (current->data.id == searchId) {
            return current; 
        }
        
        current = current->next;
    }
    
    return NULL; 
}

void searchListByName(const char* targetName){
    Node* current = head;
    bool foundAny = false;

    Serial.print("--- Searching for Name: '");
    Serial.print(targetName);
    Serial.println("' ---");

    while (current != NULL) {
        
        if (strcmp(current->data.nama, targetName) == 0) {
            
            Serial.print("- Found! ID: ");
            Serial.print(current->data.id);
            Serial.print(" | Stock: ");
            Serial.println(current->data.stock);
            
            foundAny = true;
        }
        
        current = current->next;
    }

    if (!foundAny) {
        Serial.println("No items matched that name.");
    }
    Serial.println("-----------------------------------");
}