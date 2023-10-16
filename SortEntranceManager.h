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
        cantidadCajeros = config.cantidadDeCajeros;
        cantidadCubiculos = config.cantidadDeCubiculos;
    }



    //será un hilo
    void sortToBathStoreAudience()
    {
        int sizeGrupo = rand() % 301 + 200;
        AttenderGroup* grupo = new AttenderGroup(sizeGrupo);
        int divisorSubgrupos = (cantidadCajeros+cantidadCubiculos)/2;
        vector<AttenderGroup>* subgrupos;

        int subgrupoSize = grupo->getSize() / divisorSubgrupos;

        for (int i = 0; i < divisorSubgrupos; i++) {
            subgrupos->push_back(AttenderGroup(subgrupoSize));
        }

        for (int i = 0; !subgrupos->empty();i++){
            AttenderGroup* subGrupoAux = &subgrupos->back();
            subgrupos->pop_back();
            int random = rand() % 100 + 1;
            if (random <= posibilidadGramilla){
                queueManager->getAudienceArea()->addToWaitingStack(subGrupoAux);

            }
            else if (random <= posibilidadGramilla + posibilidadBanno){
                queueManager->getBathroom()->at(rand() % cantidadCubiculos).addToWaitingQueue(subGrupoAux);
            }
            else{
                queueManager->getStore()->at(rand() % cantidadCajeros).addToWaitingQueue(subGrupoAux);

            }
        }
    }

    


    //será un hilo
    void addToAudienciaFromBath()
    {
        for(int i = 0; i < queueManager->getBathroom()->size(); i++){
            AttenderGroup* grupo = queueManager->getBathroom()->at(i).takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingStack(grupo);
            //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }
        
    }
    void addToAudienciaFromStore()
    {
        for(int i = 0; i < queueManager->getStore()->size(); i++){
            AttenderGroup* grupo = queueManager->getStore()->at(i).takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingStack(grupo);
            //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }
        
    }

    QueueManager* getQueueManager(){
        return queueManager;
    }


};