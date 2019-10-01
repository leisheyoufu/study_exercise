#pragma once
#include "Node.h"
class SortQueue
{
public:
    SortQueue(void);
    Node *head;
    void enqueue(EightDigital *node);
    bool equal(EightDigital *digital1,EightDigital *digital2);
    bool inQueue(EightDigital *digital);
    bool delNode(EightDigital *digital);
    void refreshNode(EightDigital *digital);
    EightDigital *getNode(EightDigital *digital);
    EightDigital *dequeue();
};

