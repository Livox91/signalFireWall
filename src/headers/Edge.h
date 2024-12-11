#include "Constant.h"

#ifndef EDGE_H
#define EDGE_H
class Edge
{
public:
    Signal *signal;
    Edge *next;
    Node *start;
    Node *end;
    float weight;
    bool hasSignal;
    char Direction;
    int JunctionId;

    Edge(Node *start, Node *end, float weight, bool hasSignal = false, int JunctionId = -1, char Direction = 'a')
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
        this->hasSignal = hasSignal;
        this->JunctionId = JunctionId;
        this->signal = NULL;
        this->Direction = Direction;
        this->next = NULL;
    }
    void setSignal(int id)
    {
        Signal *signal = new Signal(id);
        this->signal = signal;
    }
};
#endif