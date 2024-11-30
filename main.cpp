
#include "src/headers/Constant.h"
#include "src/headers/Window.h"

int main()
{
    TrafficManager trafficManager;
    Map map;

    Window screen(map, trafficManager);

    while (screen.window->isOpen())
    {
        screen.draw();
    }
    return 0;
}
