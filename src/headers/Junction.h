#include "Constant.h"
#include "Edge.h"

class Junction // Also Known As Circular Linked List of Edges
{
    int id;
    int size;
    float x, y;
    char junctionType;
    Edge *rotor;

public:
    Edge *head;

    Junction(int n, float x, float y, char JunctionType, std::vector<Edge *> edges, int id)
    {
        this->id = id;
        this->size = n;
        this->junctionType = JunctionType;
        this->x = x;
        this->y = y;
        head = edges[0];
        Edge *temp = head;
        temp->setSignal(1);
        for (int i = 2; i <= n; i++)
        {
            temp->next = edges[i - 1];
            temp = temp->next;
            temp->setSignal(i);
        }
        temp->next = head;
        this->rotor = head;
    }

    void RotateSignals()
    {
        rotor->signal->changeState();
        rotor = rotor->next;
        rotor->signal->changeState();
    }

    void resetSignals()
    {
        Edge *temp = head;
        rotor = head;
        for (int i = 1; i <= this->size; i++)
        {
            temp->signal->onOff();
            temp = temp->next;
        }
        rotor->signal->changeState();
    }

    void setSignalPostion()
    {
        Edge *temp = head;
        do
        {
            if (temp->Direction == 'N')
            {
                temp->signal->setSpritePosition(x - 25, y + 20);
            }
            else if (temp->Direction == 'E')
            {
                temp->signal->setSpritePosition(x - 30, y + 3);
                temp->signal->setSpriteRotation(270);
            }
            else if (temp->Direction == 'S')
            {
                temp->signal->setSpritePosition(x, y - 23);
            }
            else if (temp->Direction == 'W')
            {

                temp->signal->setSpritePosition(x + 35, y + 3);
                temp->signal->setSpriteRotation(90);
            }
            // std::cout << temp->start->id << " " << temp->end->id << " " << temp->Direction << "  " << temp->signal->getSignalId() << std::endl;
            temp = temp->next;
        } while (temp != head);
    }

    void setPrioritySignal(Edge *n)
    {
        Edge *temp = head;
        do
        {
            if (temp->start == n->start && temp->end == n->end)
            {
                temp->signal->onPriority();
            }
            else
            {
                temp->signal->onOff();
            }

            temp = temp->next;
        } while (temp != head);
    }

    int getId()
    {
        return this->id;
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
