#include <SFML/Graphics.hpp>
#include "Map.h"

class Window
{

public:
    sf::RenderWindow *window;
    Map *map;
    Window(Map &map) : map(&map)
    {
        window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Project");
    }
    void draw()
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        for (const auto &line : map->lines)
        {
            window->draw(line);
        }
        window->display();
    }
};