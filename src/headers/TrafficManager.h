#include "Constant.h"
#include "Map.h"
class TrafficManager
{
    Map *map;

public:
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
        for (const auto &line : map->getLines())
        {
            window->draw(line);
        }
        std::vector<Junction *> junctions = map->getJunctions();
        for (auto &junction : junctions)
        {
            junction->setSignalPostion();
            junction->drawSignals(window);
        }
    }
    void CycleSignals()
    {
        std::vector<Junction *> junctions = map->getJunctions();
        for (auto &junction : junctions)
        {
            junction->RotateSignals();
        }
    }
};
