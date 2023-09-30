//Clase Abstracta para manejar las colas de espera

#ifndef _WAITINGQUEUES_
#define _WAITINGQUEUES_ 1
#include <string>
#include "listas/List.h"
#include "attender.h"

using namespace std;

class waitingQueues 
{
private:

    bool full;
    bool empty;
    int maxOccupancy;
    Queue<AttenderGroup> *waitingQueue;

public:
    waitingQueues(int pMaxOccupancy)
    {
        full = false;
        empty = true;
        maxOccupancy = pMaxOccupancy;
        waitingQueue = new List<AttenderGroup>();
    }

    
    void addToWaitingQueue(AttenderGroup *attender)
    {
        if (full)
        {
            return;
        }
        empty = false;
        waitingQueue->enqueue(attender);
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
            waitingQueue->enqueue(new AttenderGroup());
        }
    }

    AttenderGroup *takeFromWaitingQueue()
    {
        if (!full)
        {
            return;
        }   
        return waitingQueue->dequeue();
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
        return waitingQueue;
    }
};
#endif