#include "Constant.h"
#include "Signal.h"
#pragma once
class Node
{
public:
    float x;
    float y;
    int id;
    Node(float x, float y, int id)
    {
        this->x = x;
        this->y = y;
        this->id = id;
    }
};

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