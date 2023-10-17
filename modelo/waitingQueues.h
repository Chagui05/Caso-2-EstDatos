// Clase Abstracta para manejar las colas de espera

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
    int maxOccupancy;
    int promeidoPersonasPorGrupo;
    Queue<AttenderGroup> *wQueue;

public:
    waitingQueue(int pMaxOccupancy)
    {
        promeidoPersonasPorGrupo = Config("config.json").personasPorEntrada;
        full = false;
        maxOccupancy = pMaxOccupancy;
        wQueue = new List<AttenderGroup>();
    }

    void addToWaitingQueue(AttenderGroup *pAttenderGroup)
    {
        if (!full)
        {
            wQueue->enqueue(pAttenderGroup);

            if (maxOccupancy == wQueue->getSize())
            {
                full = true;
            }
        }
    }

    /*void addQuantityToWaitingQueue(int quantity)
    {
        if (!full && quantity < promeidoPersonasPorGrupo)
        {
            int personasSobrantes = promeidoPersonasPorGrupo - quantity;

            AttenderGroup *grupoDePersonasSobrantes = new AttenderGroup(personasSobrantes);
            AttenderGroup *grupoPequeño = new AttenderGroup(quantity);

            wQueue->enqueue(grupoDePersonasSobrantes);
            wQueue->enqueue(grupoPequeño);

            if (maxOccupancy == wQueue->getSize())
            {
                full = true;
            }
        }
    }*/
    AttenderGroup *takeFromWaitingQueue()
    {
        if (!full)
        {
            return nullptr;
        }
        return wQueue->dequeue();
        if (0 == wQueue->getSize())
        {
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
    Queue<AttenderGroup> *getWaitingQueue()
    {
        return wQueue;
    }
};
#endif