#include "Constant.h"

template <typename T>
class List
{

public:
    T *head;

    List()
    {
        this->head = NULL;
    }

    void insertNode(T *Node)
    {

        Node->setNext(NULL);
        Node->setPrev(NULL);

        if (this->head == NULL)
        {
            this->head = Node;
            Node->setNext(NULL);
            Node->setPrev(NULL);
        }
        else
        {
            T *temp = this->head;
            while (temp->getNext() != NULL)
            {
                temp = temp->getNext();
            }
            temp->setNext(Node);
            Node->setPrev(temp);
            Node->setNext(NULL);
        }
    }

    T *getHead()
    {
        return head;
    }

    int size()
    {
        int count = 0;
        T *temp = head;
        while (temp != NULL)
        {
            count++;
            temp = temp->getNext();
        }
        return count;
    }

    T *getNode(int index)
    {
        T *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->getNext();
        }
        return temp;
    }

    T *search(int id)
    {
        T *temp = head;
        while (temp != NULL)
        {
            if (temp->getKey() == id)
            {
                return temp;
            }
            temp = temp->getNext();
        }
        return NULL;
    }
};
