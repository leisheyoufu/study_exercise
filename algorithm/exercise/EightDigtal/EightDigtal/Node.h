#pragma once

#include <stdlib.h>
#include "EightDigital.h"
class Node
{
public:
    Node(void);
    Node *next;
    EightDigital *val;
    Node(EightDigital *val);
};

