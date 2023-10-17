// despues de las colas de entradas manda ya sea a store, bathrooom o audiencearea
#include <iostream>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "jsonManager.h"
#include "ConcertEntrance.h"
#include "queueManager.h"

using namespace std;
using json = nlohmann::json;

class SortManager
{
private:
    int attenderGroupsPorEntrar;
    int personasPorEntrar;
    float velocidadSalidaSort;
    double posibilidadGramilla;
    double posibilidadBanno;
    double posibilidadTienda;
    vector<ConcertEntrance *> *colasActivas;
    QueueManager *queueManager;
    // elementos donde se sortea

public:
    SortManager(vector<ConcertEntrance *> *pColasActivas, int pPersonasPorEntrar, int gruposPorEntrar)
    {

        colasActivas = pColasActivas;
        personasPorEntrar = pPersonasPorEntrar;

        queueManager = new QueueManager(gruposPorEntrar+100);

        Config config = Config("config.json");

        velocidadSalidaSort = config.velocidadSalidaSort;
        posibilidadGramilla = config.posibilidadGramilla;
        posibilidadBanno = config.posibilidadBanno;
        posibilidadTienda = config.posibilidadTienda;
    }

    void sortToBathStoreOrAudience()
    {
        int aAudiencia = floor(personasPorEntrar * posibilidadGramilla);
        int aBanno = floor(personasPorEntrar * posibilidadBanno);
        int aStore = floor(personasPorEntrar * posibilidadTienda);
        aAudiencia += personasPorEntrar - (aAudiencia + aBanno + aStore); // como arriba se esta diviendo exacto, van a faltar personas, por lo que se le agrega a audiencia

        queueManager->addQuantityToBath(aBanno); // logica manejada en funcion hilo de QueueManager
        queueManager->addQuantityToStore(aStore);        // logica manejada en funcion hilo de QueueManager
        queueManager->addQuantityToAudiencia(aAudiencia);// logica manejada en funcion hilo de QueueManager
    }


    void addToAudienciaFromBath()// logica manejada en funcion hilo de QueueManager
    {
        for (int i = 0; i < queueManager->getBathroom()->size(); i++)
        {
            AttenderGroup *grupo = queueManager->getBathroom()->at(i)->takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingStack(grupo);
            // std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }
    }
    void addToAudienciaFromStore()// logica manejada en funcion hilo de QueueManager
    {
        for (int i = 0; i < queueManager->getStore()->size(); i++)
        {
            AttenderGroup *grupo = queueManager->getStore()->at(i)->takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingStack(grupo);
            // std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }
    }

    QueueManager *getQueueManager()
    {
        return queueManager;
    }
};