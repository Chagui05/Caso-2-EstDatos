//Clase para manejar el stage/gramilla, contienen un id, si esta ocupado o no y la cantidad de ellos que hay

#ifndef _AUDIENCEAREA_
#define _AUDIENCEAREA_ 1
#include <string>
#include <thread>
#include "listas/List.h"
#include "attender.h"

using namespace std;

class AudienceArea
{
private: 

    bool full;
    bool empty;
    int maxOccupancy;
    Stack<AttenderGroup> *wStack;

public:
        
    AudienceArea(int pMaxOccupancy)
    {
        full = false;
        empty = true;
        maxOccupancy = pMaxOccupancy;
        wStack = new List<AttenderGroup>();
    }

    
    void addToWaitingQueue(AttenderGroup *attender)
    {
        if (full)
        {
            return;
        }
        empty = false;
        wStack->push(attender);
    }
    
    //hilo
    void addQuantityToWaitingQueue(int quantity)
    {
        if (full)
        {
            return;
        }
        empty = false;
        for (int i = 0; i < quantity; i++)
        {
            wStack->push(new AttenderGroup());
        }
    }

    AttenderGroup *takeFromWaitingQueue()
    {
        if (!full)
        {
            return;
        }   
        return wStack->pop();
    }

    bool getFull()
    {
        return full;
    }

    void setFull()
    {
        full = true;
    }

    Stack<AttenderGroup>* getWaitingQueue()
    {
        return wStack;
    }
};
#endif