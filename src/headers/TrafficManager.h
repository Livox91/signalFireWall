#include "Constant.h"
#include "Map.h"
class TrafficManager
{
    std::vector<Node *> shortestPath;

public:
    Map *map;
    TrafficManager(Map &map) : map(&map)
    {
        map.setlines();
        map.setNodesAndEdges();
        map.setJunctions();
        map.setGraph();
    }

    void drawMap(sf::RenderWindow *window)
    {

        window->draw(map->getSprite());
        // for (const auto &line : map->getLines())
        // {
        //     window->draw(line);
        // }
        map->drawJunctions(window);
    }
    void CycleSignals()
    {
        std::vector<Junction *> junctions = map->getJunctions();
        for (auto &junction : junctions)
        {
            junction->RotateSignals();
        }
    }
    std::vector<Node *> ShortestPath(int srcID, int destID)
    {
        shortestPath = map->ShortestPath(srcID, destID);
        return shortestPath;
    }

    void drawShortestPath(sf::RenderWindow *window)
    {

        for (int i = 0; i < shortestPath.size() - 1; i++)
        {
            sf::Vector2f start = {shortestPath[i]->x, shortestPath[i]->y};
            sf::Vector2f end = {shortestPath[i + 1]->x, shortestPath[i + 1]->y};

            for (auto &line : map->getLines())
            {
                if (arePointsClose(line[0].position, start) && arePointsClose(line[line.getVertexCount() - 1].position, end))
                {
                    line[0].color = sf::Color::Red;
                    line[line.getVertexCount() / 2].color = sf::Color::Red;
                    line[line.getVertexCount() - 1].color = sf::Color::Red;
                    window->draw(line);
                }
            }
        }
    }
    bool arePointsClose(const sf::Vector2f &a, const sf::Vector2f &b, float proximity = 4.0f)
    {
        return std::abs(a.x - b.x) <= proximity && std::abs(a.y - b.y) <= proximity;
    }
};
