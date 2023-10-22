// despues de las colas de entradas manda ya sea a store, bathrooom o audiencearea
#include <iostream>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "jsonManager.h"
#include "modelo/ConcertEntrance.h"
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
    QueueManager *queueManager;
    // elementos donde se sortea

public:
    SortManager(int pPersonasPorEntrar, int gruposPorEntrar)
    {
        personasPorEntrar = pPersonasPorEntrar;

        queueManager = new QueueManager(gruposPorEntrar+100);
    
        Config config = Config("config.json");

        velocidadSalidaSort = config.velocidadSalidaSort;
        posibilidadGramilla = config.posibilidadGramilla;
        posibilidadBanno = config.posibilidadBanno;
        posibilidadTienda = config.posibilidadTienda;
        cout<<"SortManager instanciado"<<endl;
        
    }

    void sortToBathStoreOrAudience()
    {
        int aAudiencia = floor(personasPorEntrar * posibilidadGramilla);
        int aBanno = floor(personasPorEntrar * posibilidadBanno);
        int aStore = floor(personasPorEntrar * posibilidadTienda);
        aAudiencia += personasPorEntrar - (aAudiencia + aBanno + aStore); // como arriba se esta diviendo exacto, van a faltar personas, por lo que se le agrega a audiencia

        // queueManager->addQuantityToBath(aBanno); // logica manejada en funcion hilo de QueueManager
        // queueManager->addQuantityToStore(aStore);        // logica manejada en funcion hilo de QueueManager
        // queueManager->addQuantityToAudiencia(aAudiencia);// logica manejada en funcion hilo de QueueManager
        
        queueManager->startThreads(aBanno);
    }


    void addToAudiencia_FromBathAndStore()
    {
        queueManager->storeToAudiencia();// logica manejada en funcion hilo de QueueManager
        queueManager->bathToAudiencia();// logica manejada en funcion hilo de QueueManager
    }

    QueueManager *getQueueManager()
    {
        return queueManager;
    }
};