
#include "src/headers/Constant.h"
#include "src/headers/Window.h"

int main()
{
    Map map;
    TrafficManager trafficManager(map);

    Window screen(trafficManager);

    while (screen.window->isOpen())
    {
        screen.draw();
    }
    return 0;
}