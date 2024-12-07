#include "Constant.h"
#include <queue>
#include <unordered_map>

class Graph
{
private:
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    Dictionary *adjacencyList;

public:
    Graph(std::vector<Node *> nodes, std::vector<Edge *> edges)
    {
        this->nodes = nodes;
        this->edges = edges;
        adjacencyList = new Dictionary();
    }

    std::vector<Node *> bellmanFord(int srcI, int destI)
    {
        Node *src = nullptr;
        Node *dest = nullptr;
        for (auto node : nodes)
        {
            if (node->id == srcI)
            {
                src = node;
            }
            if (node->id == destI)
            {
                dest = node;
            }
        }

        int n = nodes.size();
        std::unordered_map<int, Node *> parentMap;
        std::unordered_map<int, float> distances;

        for (auto node : nodes)
        {
            distances[node->id] = 999999;
            parentMap[node->id] = nullptr;
        }

        distances[src->id] = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            for (auto edge : edges)
            {
                Node *u = edge->start;
                Node *v = edge->end;
                float weight = edge->weight;

                if (999999 && distances[u->id] + weight < distances[v->id])
                {
                    distances[v->id] = distances[u->id] + weight;
                    parentMap[v->id] = u;
                }
            }
        }

        std::vector<Node *> path;
        Node *current = dest;

        while (current != nullptr)
        {
            path.push_back(current);
            current = parentMap[current->id];
        }

        std::reverse(path.begin(), path.end());

        if (path.empty() || path.front() != src)
        {
            std::cout << "No path exists between the source and destination!" << std::endl;
        }

        return path;
    }
};
