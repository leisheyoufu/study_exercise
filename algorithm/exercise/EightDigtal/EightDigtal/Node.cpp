#include "Node.h"


Node::Node(void)
{
}
Node::Node(EightDigital *val)
{
    this->val = val;
    this->next = NULL;
}