#include "Constant.h"

#ifndef NODE_H
#define NODE_H
class Node
{
public:
    Node *next;
    Node *prev;
    float x;
    float y;
    int id;
    Node(float x, float y, int id)
    {
        this->next = NULL;
        this->prev = NULL;
        this->x = x * scale + offsetX;
        this->y = WIN_HEIGHT - (y * scale + offsetY);
        this->id = id;
    }
    void setNext(Node *next)
    {
        this->next = next;
    }

    void setPrev(Node *prev)
    {
        this->prev = prev;
    }

    Node *getNext()
    {
        return next;
    }

    Node *getPrev()
    {
        return prev;
    }
};

#endif