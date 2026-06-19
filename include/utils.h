#ifndef UTILS_H
#define UTILS_H

#include "global.h"

Status intToStatus(unsigned int pilihan);
void saveNodeToFlash(int node_index, Node* newNodeData);
Node readNodeFromFlash(int node_index);
void printSemuaNode(int head_index);

#endif