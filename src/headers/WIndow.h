#include "TrafficManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Debouncer.h"
class Window
{

public:
    sf::RenderWindow *window;
    MouseDebouncer *debouncer;

    TrafficManager *trafficManager;
    sf::Clock clock;
    Node *startNode;
    Node *endNode;
    std::vector<Node *> shortestPath;

    Window(TrafficManager &trafficManager) : trafficManager(&trafficManager)
    {
        window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT - 200), "Project");
        debouncer = new MouseDebouncer(200);
    }

    void draw()
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f clickPos = window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if (debouncer->isDebouncedClick(sf::Mouse::Left))
                {

                    startNode = trafficManager->map->getNearestNode(clickPos);
                    std::cout << "Start Node: " << startNode->id << std::endl;
                }
                else if (debouncer->isDebouncedClick(sf::Mouse::Right))
                {
                    endNode = trafficManager->map->getNearestNode(clickPos);
                    std::cout << "End Node: " << endNode->id << std::endl;
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    std::cout << "Shortest Path: ";
                    if (startNode != NULL && endNode != NULL)
                    {
                        shortestPath = trafficManager->map->ShortestPath(startNode->id, endNode->id);
                        for (auto &node : shortestPath)
                        {
                            std::cout << node->id << " ";
                        }
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window->close();
        }
        if (clock.getElapsedTime().asSeconds() >= 5.0f)
        {
            trafficManager->CycleSignals();
            clock.restart();
        }
        window->clear();

        // trafficManager->drawMap(window);

        for (const auto &node : trafficManager->map->getNodes())
        {
            sf::CircleShape circle(3);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(node->x, node->y);
            window->draw(circle);
        }

        window->display();
    }
};