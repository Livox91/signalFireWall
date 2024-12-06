#include "Constant.h"
#include <queue>

class Graph
{
private:
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    Dictionary *adjacencyList;
    int size;

public:
    Graph(std::vector<Node *> nodes, std::vector<Edge *> edges)
    {
        this->nodes = nodes;
        this->edges = edges;
        this->size = findMaxID();
        adjacencyList = new Dictionary();
    }

    void setAdjacencyList()
    {

        for (const auto &edge : edges)
        {
            adjacencyList->insert(edge->start->id, edge->start);
            adjacencyList->insert(edge->start->id, edge->end);
            adjacencyList->insert(edge->end->id, edge->end);
            adjacencyList->insert(edge->end->id, edge->start);
        }
    }

    int findMaxID()
    {
        int max = 0;
        for (const auto &node : nodes)
        {
            if (node->id > max)
            {
                max = node->id;
            }
        }
        return max;
    }

    void printGraph()
    {
        adjacencyList->printDictionary();
    }
};
