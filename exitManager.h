#ifndef _EXITMANAGER_
#define _EXITMANAGER_ 1
#include <string>
#include <thread>
#include "listas/List.h"
#include "attender.h"
#include "queueManager.h"

using namespace std;

class exitManager
{
private:
    bool timeToExit;
    QueueManager *queueManager;
    int cantidadDeGrupos;
    List<AttenderGroup> *personasSalidas;

public:
    exitManager(QueueManager *pQueueManager)
    {
        timeToExit = false;
        queueManager = pQueueManager;
        personasSalidas = new List<AttenderGroup>();
    }

    // hilo
    List<AttenderGroup>* exit()
    {
        if (timeToExit == true)
        {
            while (queueManager->getAudienceArea()->getWaitingStack()->getSize() > 0)
            {
                personasSalidas->enqueue(queueManager->getAudienceArea()->takeFromWaitingStack());
            }
        }
        return personasSalidas;
    }
    void setTrueExit()
    {
        timeToExit = true;
    }
};

#endif