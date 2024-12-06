#include "Constant.h"

#ifndef PAIR_H
#define PAIR_H

template <typename T1, typename T2>
class Pair
{
public:
    Pair *next;
    Pair *prev;
    T1 first;
    T2 second;

    Pair()
    {
        next = NULL;
        prev = NULL;
    }

    T1 getKey()
    {
        return first;
    }
    T2 getValue()
    {
        return second;
    }

    void setNext(Pair *next)
    {
        this->next = next;
    }

    void setPrev(Pair *prev)
    {
        this->prev = prev;
    }

    Pair *getNext()
    {
        return next;
    }

    Pair *getPrev()
    {
        return prev;
    }

    void makePair(T1 first, T2 second)
    {
        this->first = first;
        this->second = second;
    }
};

#endif