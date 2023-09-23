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
    int maxOccupancy;
    Queue<AttenderGroup> *waitingQueue;

public:
    waitingQueues(int pMaxOccupancy)
    {
        full = false;
        maxOccupancy = pMaxOccupancy;
        waitingQueue = new List<AttenderGroup>();
    }

    void addToWaitingQueue(AttenderGroup *attender)
    {
        waitingQueue->enqueue(attender);
    }

    AttenderGroup *takeFromWaitingQueue()
    {
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
};
#endif