#include "Constant.h"

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
    Node *start;
    Node *end;
    float weight;
    Edge(Node *start, Node *end, float weight)
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
};