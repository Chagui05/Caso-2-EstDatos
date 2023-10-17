#include <iostream>
#include <fstream>
#include <thread>
#include "json.hpp"
#include "jsonManager.h"
#include "ConcertEntrance.h"
#include "queueManager.h"

using namespace std;
using json = nlohmann::json;

class concertManager
{
private:

    QueueManager* queueManager;
    AudienceArea* audienciaPrincipal;
    float proccessDuration; //sacarlo del json
    float velocidadSalidaSort;
    double posibilidadGramilla;
    double posibilidadBanno; 
    double posibilidadTienda;
    int cantidadBannos;
    int cantidadStore;

public:

    concertManager(QueueManager* pQueueManager)
    {
        queueManager = pQueueManager;
        audienciaPrincipal = queueManager->getAudienceArea();
        proccessDuration = 2.0;//cambiar y que se saque del json 
        Config config = loadConfig("config.json");
        velocidadSalidaSort = config.velocidadSalidaSort;
        posibilidadGramilla = config.posibilidadGramilla;
        posibilidadBanno = config.posibilidadBanno;
        posibilidadTienda = config.posibilidadTienda;
        cantidadStore = config.cantidadDeStore
        cantidadBannos = config.cantidadDeBannos;
    }

    // será un hilo
    void takeToBath()
    {   
        AttenderGroup* pAttenderGroup = audienciaPrincipal->takeFromWaitingQueue();

        // Calcular el tamaño de cada subgrupo
        int divisorSubgrupos = pAttenderGroup->getSize()/cantidadBannos
        int subgrupoSize = pAttenderGroup->getSize() / numSubgrupos;
        vector<AttenderGroup> subgrupos;

        for (int i = 0; i<divisorSubgrupos;i++){
            subgrupos.push_back(new AttenderGroup(subgrupoSize));
        }

        for (int i = 0; !subgrupos.empty();i++){
            queueManager->addToBath(subgrupos.back());
            subgrupos.pop_back();
        //std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));
        }
    }
    void addToAudienciaFromBath()
    {
        for(int i = 0; i < queueManager->getBathroom()->size(); i++){
            AttenderGroup* grupo = queueManager->getBathroom()->at(i).takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingStack(grupo);
            //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }   
    }
    void takeToStore()
    {
        AttenderGroup* pAttenderGroup = audienciaPrincipal->takeFromWaitingQueue();

        // Calcular el tamaño de cada subgrupo
        int divisorSubgrupos = pAttenderGroup->getSize()/cantidadStore
        int subgrupoSize = pAttenderGroup->getSize() / numSubgrupos;
        vector<AttenderGroup> subgrupos;

        for (int i = 0; i<divisorSubgrupos;i++){
            subgrupos.push_back(new AttenderGroup(subgrupoSize));
        }

        for (int i = 0; !subgrupos.empty();i++){
            queueManager->addToStore(subgrupos.back());
            subgrupos.pop_back();
        //std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));
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
};