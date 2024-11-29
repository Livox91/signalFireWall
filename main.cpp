
#include "src/headers/Constant.h"
#include "src/headers/Window.h"

int main()
{
    Map map;
    Window screen(map);

    while (screen.window->isOpen())
    {
        screen.draw();
    }

    return 0;
}
