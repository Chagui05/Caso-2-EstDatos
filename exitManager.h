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
    int velocidadSalida;

public:
    exitManager(QueueManager *pQueueManager)
    {
        timeToExit = false;
        queueManager = pQueueManager;
        personasSalidas = new List<AttenderGroup>();
        Config config = Config("config.json");
        velocidadSalida = config.velocidadSalidaSort;
    }

    // hilo
    List<AttenderGroup>* exit()
    {
        if (timeToExit == true)
        {
            std::vector<std::thread> threads;
            for (int i = 0; i < queueManager->getAudienceArea()->getWaitingStack()->getSize(); i++)
            {
                threads.emplace_back([this, i]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>( velocidadSalida* 1000)));
                    AttenderGroup* grupo = queueManager->getAudienceArea()->takeFromWaitingStack();
                    personasSalidas->enqueue(grupo);
                });
            }

            for (auto& thread : threads)
            {
                thread.join();
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