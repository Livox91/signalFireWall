#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Junction.h"

class Window
{

public:
    sf::RenderWindow *window;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    Map *map;

    Window(Map &map) : map(&map)
    {
        window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT - 200), "Project");
        if (!mapTexture.loadFromFile(MapImagePath))
        {
            std::cerr << "Failed to load map image!" << std::endl;
        }
        mapSprite.setTexture(mapTexture);
        mapSprite.setPosition(0, 0);
        mapSprite.setScale(1.3318, 1.3318);
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
        window->draw(mapSprite);
        window->display();
    }
};