#include "Constant.h"
#include "Signal.h"
class Junction
{
    float x, y;

public:
    Signal *head;
    Junction(int n, float x, float y)
    {
        this->x = x;
        this->y = y;
        head = new Signal(1);
        Signal *temp = head;
        for (int i = 2; i <= n; i++)
        {
            Signal *newSignal = new Signal(1);
            temp->next = newSignal;
            temp = newSignal;
        }
        temp->next = head;
    }
    void RotateSignals()
    {
        Signal *temp = head;
        while (temp->next != head)
        {
            temp->changeState();
            temp = temp->next;
        }
    }
    void setSignalPostion()
    {
        Signal *temp = head;

        temp->setSpritePosition(x, y + 20);
        temp = temp->next;
        temp->setSpritePosition(x + 20, y);
        temp->setSpriteRotation(90);
        temp = temp->next;
        temp->setSpritePosition(x, y - 20);
        temp = temp->next;
        temp->setSpritePosition(x - 20, y);
        temp->setSpriteRotation(270);
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
