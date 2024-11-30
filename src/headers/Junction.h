#include "Constant.h"
#include "Signal.h"
class Junction
{
    float x, y;
    char junctionType;
    Signal *rotor;

public:
    Signal *head;
    Junction(int n, float x, float y, char JunctionType)
    {
        this->junctionType = JunctionType;
        this->x = x;
        this->y = y;
        head = new Signal(1);
        Signal *temp = head;
        for (int i = 2; i <= n; i++)
        {
            Signal *newSignal = new Signal(i);
            temp->next = newSignal;
            temp = newSignal;
        }
        temp->next = head;
        this->rotor = head;
    }
    void RotateSignals()
    {
        rotor->changeState();
        if (rotor->getSignalState())
        {
            rotor->changeState();
        }
        rotor = rotor->next;
        rotor->changeState();
    }
    void setSignalPostion()
    {
        Signal *temp = head;
        if (junctionType == 'a')
        {
            temp->setSpritePosition(x - 25, y + 20);
            temp = temp->next;
            temp->setSpritePosition(x + 35, y + 3);
            temp->setSpriteRotation(90);
            temp = temp->next;
            temp->setSpritePosition(x, y - 23);
            temp = temp->next;
            temp->setSpritePosition(x - 30, y + 3);
            temp->setSpriteRotation(270);
        }
        else if (junctionType == 'b')
        {
            temp->setSpritePosition(x - 25, y + 20);
            temp = temp->next;
            temp->setSpritePosition(x + 35, y + 3);
            temp->setSpriteRotation(90);
            temp = temp->next;
            temp->setSpritePosition(x - 30, y + 3);
            temp->setSpriteRotation(270);
        }
        else if (junctionType == 'c')
        {
            temp->setSpritePosition(x - 25, y + 20);
            temp = temp->next;
            temp->setSpritePosition(x, y - 23);
            temp = temp->next;
            temp->setSpritePosition(x - 30, y + 3);
            temp->setSpriteRotation(270);
        }
        else if (junctionType == 'd')
        {
            temp->setSpritePosition(x + 35, y + 3);
            temp->setSpriteRotation(90);
            temp = temp->next;
            temp->setSpritePosition(x, y - 23);
            temp = temp->next;
            temp->setSpritePosition(x - 30, y + 3);
            temp->setSpriteRotation(270);
        }
    }
    void setPrioritySignal(int n)
    {
        Signal *temp = head;
        for (int i = 1; i < n; i++)
        {
            if (temp->getSignalId() == n)
            {
                temp->onPriority();
            }
            temp = temp->next;
            temp->onOff();
        }
    }

    void drawSignals(sf::RenderWindow *window)
    {

        Signal *temp = head;
        do
        {
            window->draw(temp->getSignalSprite());
            temp = temp->next;
        } while (temp != head);
    }
};
