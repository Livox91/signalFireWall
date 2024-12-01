#include <SFML/Graphics.hpp>
#include "Map.h"
#include "TrafficManager.h"

class Window
{

public:
    sf::RenderWindow *window;
    Map *map;
    TrafficManager *trafficManager;
    sf::Clock clock;
    std::vector<int> shortestPath;
    Window(Map &map, TrafficManager &trafficManager) : map(&map), trafficManager(&trafficManager)
    {
        window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT - 200), "Project");
        this->map->setlines();
        this->map->setEdges();
        this->map->setGraph();
        this->map->print();
        shortestPath = this->map->ShortestPath(1, 112);
    }
    void draw()
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        if (clock.getElapsedTime().asSeconds() >= 5.0f)
        {
            trafficManager->CycleSignals();
            clock.restart();
        }
        window->clear();

        for (const auto &line : map->getLines())
        {
            // window->draw(line);
        }
        for (const auto &edge : map->getEdges())
        {
            sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(edge->start->x * scale + offsetX, WIN_HEIGHT - (edge->start->y * scale + offsetY))),
                    sf::Vertex(sf::Vector2f(edge->end->x * scale + offsetX, WIN_HEIGHT - (edge->end->y * scale + offsetY))),

                };
            window->draw(line, 2, sf::Lines);
        }
        if (!shortestPath.empty())
        {
            std::cout << "Shortest path: ";
            for (int id : shortestPath)
            {
                std::cout << id << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "No valid path exists." << std::endl;
        }
        window->draw(map->getSprite());
        trafficManager->drawJunction(window);
        window->display();
    }
};