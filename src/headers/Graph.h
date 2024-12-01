#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <iostream>
#include "Node.h"

class Graph
{
private:
    std::unordered_map<int, Node *> nodes; // Store nodes by ID
    std::vector<Edge *> edges;             // List of all edges
    std::unordered_map<int, std::vector<Edge *>> adjacencyList;

public:
    Graph()
    {
        adjacencyList = calculateAdjacencyList(edges);
    }
    // Add a node
    void addNodes(std::vector<Node *> nodes)
    {
        for (const auto &node : nodes)
        {
            this->nodes[node->id] = node;
        }
    }

    // Add an edge
    void addEdge(std::vector<Edge *> edges)
    {
        for (const auto &edge : edges)
        {
            this->edges.push_back(edge);
        }
    }
    std::unordered_map<int, std::vector<Edge *>> calculateAdjacencyList(const std::vector<Edge *> &edges)
    {
        std::unordered_map<int, std::vector<Edge *>> adjacencyList;

        for (const auto &edge : edges)
        {
            // Add the edge to the adjacency list of the start node
            adjacencyList[edge->start->id].push_back(edge);
        }

        return adjacencyList;
    }
    std::vector<int> dijkstra(int srcId, int destId)
    {
        int nodeCount = nodes.size();
        // Priority queue: <distance, node ID>
        std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<>>
            pq;

        // Initialize distances and parent vectors
        std::vector<float> distances(nodeCount, std::numeric_limits<float>::infinity());
        std::vector<int> parent(nodeCount, -1);
        distances[srcId] = 0;

        // Push the source node into the priority queue
        pq.push({0, srcId});

        while (!pq.empty())
        {
            int currentId = pq.top().second;
            float currentDistance = pq.top().first;
            pq.pop();

            // Skip if distance is stale
            if (currentDistance > distances[currentId])
            {
                continue;
            }

            // Explore neighbors
            for (const auto &edge : adjacencyList[currentId])
            {
                int neighborId = edge->end->id;
                float newDistance = distances[currentId] + edge->weight;

                // Relaxation: Update distance if a shorter path is found
                if (newDistance < distances[neighborId])
                {
                    distances[neighborId] = newDistance;
                    parent[neighborId] = currentId;
                    pq.push({newDistance, neighborId});
                }
            }
        }

        // Reconstruct path from destId to srcId
        if (distances[destId] == std::numeric_limits<float>::infinity())
        {
            return {}; // No valid path exists
        }

        std::vector<int> path;
        for (int current = destId; current != -1; current = parent[current])
        {
            path.push_back(current);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
    // Debug: Print all nodes and edges
    void printGraph()
    {
        std::cout << "Nodes:" << std::endl;
        for (const auto &[id, node] : nodes)
        {
            std::cout << "  ID: " << node->id << " (x: " << node->x << ", y: " << node->y << ")" << std::endl;
        }

        std::cout << "Edges:" << std::endl;
        for (const auto &edge : edges)
        {
            std::cout << "  Start: " << edge->start->id << ", End: " << edge->end->id
                      << ", Weight: " << edge->weight << std::endl;
        }
    }
};
