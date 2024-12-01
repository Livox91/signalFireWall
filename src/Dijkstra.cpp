std::vector<int> findShortestPath(int srcId, int destId)
{
    // Priority queue for Dijkstra: <distance, node ID>
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<>> pq;

    // Distance map (initialize all distances to infinity)
    std::unordered_map<int, float> distances;
    for (const auto &[id, node] : nodes)
    {
        distances[id] = std::numeric_limits<float>::infinity();
    }
    distances[srcId] = 0;

    // Parent map for path reconstruction
    std::unordered_map<int, int> parent;
    parent[srcId] = -1; // Source has no parent

    // Push the source node into the queue
    pq.push({0, srcId});

    while (!pq.empty())
    {
        int currentId = pq.top().second;
        float currentDistance = pq.top().first;
        pq.pop();

        // Skip if we find a stale distance
        if (currentDistance > distances[currentId])
            continue;

        // Explore neighbors (edges starting from the current node)
        for (const auto &edge : edges)
        {
            if (edge->start->id == currentId)
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
    }

    // Reconstruct the path from destId to srcId
    std::vector<int> path;
    int current = destId;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    std::reverse(path.begin(), path.end()); // Reverse the path

    // Check if the path starts with srcId (valid path)
    if (!path.empty() && path[0] == srcId)
    {
        return path;
    }
    else
    {
        return {}; // Return empty path if no valid path exists
    }
}