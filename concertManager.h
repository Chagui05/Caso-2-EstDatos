#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "jsonManager.h"
#include "queueManager.h"

using namespace std;
using json = nlohmann::json;

class concertManager
{
private:
    QueueManager *queueManager;
    float proccessDuration; // sacarlo del json
    float velocidadSalidaSort;
    double posibilidadBanno;
    double posibilidadTienda;

public:
    concertManager(QueueManager *pQueueManager)
    {
        queueManager = pQueueManager;
        proccessDuration = 2.0; // cambiar y que se saque del json
        Config config = Config("config.json");
        velocidadSalidaSort = config.velocidadSalidaSort;
        posibilidadBanno = config.posibilidadBanno;
        posibilidadTienda = config.posibilidadTienda;
        
    }

    void takeToBath()
    {
        AttenderGroup *grupo = queueManager->getAudienceArea()->takeFromWaitingStack();
        queueManager->addQuantityToBath(grupo->getSize()); // logica manejada en funcion hilo de QueueManager
        // con un for queueManager->getBathroom()->at(i)->addToWaitingQueue(grupo); // logica manejada en funcion hilo de QueueManager
    }

    void addToAudienciaFromBath()
    {
        queueManager->bathToAudiencia(); // logica manejada en funcion hilo de QueueManager
    }

    void takeToStore()
    {
        AttenderGroup *grupo = queueManager->getAudienceArea()->takeFromWaitingStack();
        queueManager->addQuantityToStore(grupo->getSize()); // logica manejada en funcion hilo de QueueManager
    }

    void addToAudienciaFromStore()
    {
        queueManager->storeToAudiencia(); // logica manejada en funcion hilo de QueueManager
    }


    void sortToBathOrStore()
    {
        std::srand(std::time(0));
        double aleatorio = static_cast<double>(std::rand()) / RAND_MAX;

        if (aleatorio < posibilidadBanno)
        {
            takeToBath();
        }
        else
        {
            takeToStore();
        }
    }

    QueueManager* getQueueManager()
    {
        return queueManager;
    }
};