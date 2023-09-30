//Clase Abstracta para manejar las colas de espera

#ifndef _WAITINGQUEUES_
#define _WAITINGQUEUES_ 1
#include <string>
#include "listas/List.h"
#include "attender.h"

using namespace std;

class waitingQueue 
{
private:

    bool full;
    bool empty;
    int maxOccupancy;
    Queue<AttenderGroup> *wQueue;

public:
    waitingQueue(int pMaxOccupancy)
    {
        full = false;
        empty = true;
        maxOccupancy = pMaxOccupancy;
        wQueue = new List<AttenderGroup>();
    }

    
    void addToWaitingQueue(AttenderGroup *attender)
    {
        if (full)
        {
            return;
        }
        
        empty = false;
        wQueue->enqueue(attender);

        if (maxOccupancy == wQueue->getSize())
        {
            full = true;
        }
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
            wQueue->enqueue(new AttenderGroup());
        }
    }

    AttenderGroup *takeFromWaitingQueue()
    {
        if (!full)
        {
            return;
        }   
        return wQueue->dequeue();
        if (0 == wQueue->getSize())
        {
            empty = true;
            full = false;
        }
    }

    bool getFull()
    {
        return full;
    }

    void setFull()
    {
        full = true;
    }
    Queue<AttenderGroup>* getWaitingQueue()
    {
        return wQueue;
    }
};
#endif