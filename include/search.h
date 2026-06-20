#ifndef SEARCH_H
#define SEARCH_H

#include "global.h"
#include "linked_list.h"

Node* searchListByID(unsigned int searchId);
void searchListByName(const char* targetName);
void searchItemByName(Node* head);

#endif