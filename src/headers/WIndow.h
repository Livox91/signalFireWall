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
    Window(Map &map, TrafficManager &trafficManager) : map(&map), trafficManager(&trafficManager)
    {
        window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT - 200), "Project");
        this->map->setlines();
        this->map->print();
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

            window->draw(line);
        }

        window->draw(map->getSprite());
        trafficManager->drawJunction(window);
        window->display();
    }
};