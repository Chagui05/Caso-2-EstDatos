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
    }

    //será un hilo
    void sortToBathStoreAudience()
    {
        while(gruposPorEntrar > 0){

            for(int j = 0; j < colasActivas->size() && gruposPorEntrar > 0 ; j++){

                float randomNum = static_cast<float>(rand()) / RAND_MAX;
                AttenderGroup* grupo = colasActivas->at(j).takeFromWaitingQueue();

                if (randomNum < posibilidadGramilla) {
                    queueManager->getAudienceArea()->addToWaitingQueue(grupo);
                } 
                else if (randomNum < posibilidadGramilla + posibilidadBanno) {
                    queueManager->addToBath(grupo);   
                } 
                else 
                {
                    queueManager->addToStore(grupo);
                }
                gruposPorEntrar--;
                //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));  
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