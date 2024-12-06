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
    int JunctionId;

    Edge(Node *start, Node *end, float weight, bool hasSignal = false, int JunctionId = -1)
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
        this->hasSignal = hasSignal;
        this->JunctionId = JunctionId;
        this->signal = NULL;
        this->next = NULL;
    }
    void setSignal()
    {
        Signal *signal = new Signal(this->JunctionId);
        this->signal = signal;
    }
};
#endif