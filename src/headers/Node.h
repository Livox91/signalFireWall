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
    int signalId;

    Edge(Node *start, Node *end, float weight, bool hasSignal = false, int signalId = -1)
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
        this->hasSignal = hasSignal;
        this->signalId = signalId;
        this->signal = NULL;
        this->next = NULL;
    }
    void setSignal()
    {
        Signal *signal = new Signal(this->signalId);
        this->signal = signal;
    }
};