#include "Constant.h"

class MouseDebouncer
{
public:
    MouseDebouncer(float debounceTimeMs)
        : debounceTime(sf::milliseconds(debounceTimeMs)) {}

    bool isDebouncedClick(sf::Mouse::Button button)
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            if (clock.getElapsedTime() > debounceTime)
            {
                clock.restart();
                return true;
            }
        }
        return false;
    }

private:
    sf::Clock clock;
    sf::Time debounceTime;
};
