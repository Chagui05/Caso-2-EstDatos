//despues de las colas de entradas manda ya sea a store, bathrooom o audiencearea
#include <iostream>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include "jsonManager.h"
#include "ConcertEntrance.h"
#include "queueManager.h"


using namespace std;
using json = nlohmann::json;

class SortEntranceManager
{
private:

    int gruposPorEntrar;
    float velocidadSalidaSort;
    double posibilidadGramilla;
    double posibilidadBanno; 
    double posibilidadTienda;
    int cantidadCubiculos;
    int cantidadCajeros;
    vector<ConcertEntrance>* colasActivas;
    QueueManager* queueManager;
    //elementos donde se sortea
    

public:

    SortEntranceManager(vector<ConcertEntrance>* pColasActivas, int pGruposPorEntrar)
    {

        colasActivas = pColasActivas;
        gruposPorEntrar = pGruposPorEntrar;
        queueManager = new QueueManager(gruposPorEntrar);
        Config config = loadConfig("config.json");
        
        velocidadSalidaSort = config.velocidadSalidaSort;
        posibilidadGramilla = config.posibilidadGramilla;
        posibilidadBanno = config.posibilidadBanno;
        posibilidadTienda = config.posibilidadTienda;
        cantidadCajeros = config.cantidadDeCajeros
        cantidadCubiculos = config.cantidadDeCubiculos;
    }

    //será un hilo
    void sortToBathStoreAudience()
    {
        int numGruposPorEntrar = gruposPorEntrar;

        while (numGruposPorEntrar > 0)
        {
            // Generar un numero aleatorio entre 200 y 500 para el tamaño del proximo grupo

            int sizeGrupo = rand() % 301 + 200;
            // Numero generado de la cantidad de cajeros y de bannos
            int divisorSubgrupos = (cantidadCajeros+cantidadCubiculos)/2

            // Dividir el grupo en subgrupos
            int numSubgrupos = sizeGrupo / divisorSubgrupos;
            if (sizeGrupo % 80 != 0)
            {
                numSubgrupos++;
            }

            // Distribuir aleatoriamente los subgrupos en las areas
            for (int i = 0; i < numSubgrupos; i++)
            {
                float randomNum = static_cast<float>(rand()) / RAND_MAX;
                AttenderGroup* grupo = colasActivas->at(j).takeFromWaitingQueue();

                if (randomNum < posibilidadGramilla)
                {
                    queueManager->getAudienceArea()->addToWaitingQueue(grupo);
                }
                else if (randomNum < posibilidadGramilla + posibilidadBanno)
                {
                    queueManager->addToBath(grupo);
                }
                else
                {
                    queueManager->addToStore(grupo);
                }

                // Reducir la cantidad de grupos que deben entrar
                numGruposPorEntrar--;
            }
        }
    }


    //será un hilo
    void addToAudienciaFromBath()
    {
        for(int i = 0; i < queueManager->getBathroom()->size(); i++){
            AttenderGroup* grupo = queueManager->getBathroom()->at(i).takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingQueue(grupo);
            //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }
        
    }
    void addToAudienciaFromStore()
    {
        for(int i = 0; i < queueManager->getStore()->size(); i++){
            AttenderGroup* grupo = queueManager->getStore()->at(i).takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingQueue(grupo);
            //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }
        
    }

    QueueManager* getQueueManager(){
        return queueManager;
    }


};