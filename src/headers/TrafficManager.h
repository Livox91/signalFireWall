#include "Constant.h"
#include "Junction.h"

class TrafficManager
{
    Junction *j1;
    Junction *j2;
    Junction *j3;
    Junction *j4;
    Junction *j5;
    Junction *j6;
    Junction *j7;

public:
    TrafficManager()
    {

        j1 = new Junction(4, 89.11, 89.11, 'a');
        j2 = new Junction(3, 526.67, 89.11, 'b');
        j3 = new Junction(3, 708, 89.11, 'c');
        j4 = new Junction(4, 89.11, 270.59, 'a');
        j5 = new Junction(3, 343.14, 270.59, 'b');
        j6 = new Junction(3, 708, 393.68, 'c');
        j7 = new Junction(3, 708, 578.55, 'd');
    }

    void drawJunction(sf::RenderWindow *window)
    {

        j1->setSignalPostion();
        j1->drawSignals(window);
        j2->setSignalPostion();
        j2->drawSignals(window);
        j3->setSignalPostion();
        j3->drawSignals(window);
        j4->setSignalPostion();
        j4->drawSignals(window);
        j5->setSignalPostion();
        j5->drawSignals(window);
        j6->setSignalPostion();
        j6->drawSignals(window);
        j7->setSignalPostion();
        j7->drawSignals(window);
    }
    void CycleSignals()
    {
        j1->RotateSignals();
        j2->RotateSignals();
        j3->RotateSignals();
        j4->RotateSignals();
        j5->RotateSignals();
        j6->RotateSignals();
        j7->RotateSignals();
    }
};
