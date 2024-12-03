#include <SFML/Graphics.hpp>
#include "TrafficManager.h"

class Window
{

public:
    sf::RenderWindow *window;

    TrafficManager *trafficManager;
    sf::Clock clock;
    std::vector<int> shortestPath;

    Window(TrafficManager &trafficManager) : trafficManager(&trafficManager)
    {
        window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT - 200), "Project");
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

        trafficManager->drawMap(window);

        window->display();
    }
};