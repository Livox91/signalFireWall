#include "Constant.h"
#include "Node.h"
class Junction
{
    float x, y;
    char junctionType;
    Edge *rotor;

public:
    Edge *head;
    Junction(int n, float x, float y, char JunctionType, std::vector<Edge *> edges)
    {

        this->junctionType = JunctionType;
        this->x = x;
        this->y = y;
        head = edges[0];
        Edge *temp = head;
        head->setSignal();
        for (int i = 2; i <= n; i++)
        {
            temp->next = edges[i - 1];
            temp = temp->next;
        }
        temp->next = head;
        this->rotor = head;
    }
    void RotateSignals()
    {
        rotor->signal->changeState();
        if (rotor->signal->getSignalState())
        {
            rotor->signal->changeState();
        }
        rotor = rotor->next;
        rotor->signal->changeState();
    }

    void setSignalPostion()
    {
        Edge *temp = head;
        if (junctionType == 'a')
        {
            temp->signal->setSpritePosition(x - 25, y + 20);
            temp = temp->next;
            temp->signal->setSpritePosition(x + 35, y + 3);
            temp->signal->setSpriteRotation(90);
            temp = temp->next;
            temp->signal->setSpritePosition(x, y - 23);
            temp = temp->next;
            temp->signal->setSpritePosition(x - 30, y + 3);
            temp->signal->setSpriteRotation(270);
        }
        else if (junctionType == 'b')
        {
            temp->signal->setSpritePosition(x - 25, y + 20);
            temp = temp->next;
            temp->signal->setSpritePosition(x + 35, y + 3);
            temp->signal->setSpriteRotation(90);
            temp = temp->next;
            temp->signal->setSpritePosition(x - 30, y + 3);
            temp->signal->setSpriteRotation(270);
        }
        else if (junctionType == 'c')
        {
            temp->signal->setSpritePosition(x - 25, y + 20);
            temp = temp->next;
            temp->signal->setSpritePosition(x, y - 23);
            temp = temp->next;
            temp->signal->setSpritePosition(x - 30, y + 3);
            temp->signal->setSpriteRotation(270);
        }
        else if (junctionType == 'd')
        {
            temp->signal->setSpritePosition(x + 35, y + 3);
            temp->signal->setSpriteRotation(90);
            temp = temp->next;
            temp->signal->setSpritePosition(x, y - 23);
            temp = temp->next;
            temp->signal->setSpritePosition(x - 30, y + 3);
            temp->signal->setSpriteRotation(270);
        }
    }
    void setPrioritySignal(int n)
    {
        Edge *temp = head;
        for (int i = 1; i < n; i++)
        {
            if (temp->signalId == n)
            {
                temp->signal->onPriority();
            }
            temp = temp->next;
            temp->signal->onOff();
        }
    }

    void drawSignals(sf::RenderWindow *window)
    {

        Edge *temp = head;
        do
        {
            window->draw(temp->signal->getSignalSprite());
            temp = temp->next;
        } while (temp != head);
    }
};
