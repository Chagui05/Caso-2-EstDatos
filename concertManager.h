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

public:

    concertManager(QueueManager* pQueueManager)
    {
        queueManager = pQueueManager;
        audienciaPrincipal = queueManager->getAudienceArea();
        proccessDuration = 2.0;//cambiar y que se saque del json 
    }

    // será un hilo
    void takeToBath()
    {   
        AttenderGroup* pAttender = audienciaPrincipal->takeFromWaitingQueue();
        queueManager->addToBath(pAttender);
        //std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));

    }
    void addToAudienciaFromBath()
    {
        for(int i = 0; i < queueManager->getBathroom()->size(); i++){
            AttenderGroup* grupo = queueManager->getBathroom()->at(i).takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingQueue(grupo);
            //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }   
    }
    void takeToStore()
    {
        AttenderGroup* pAttender = audienciaPrincipal->takeFromWaitingQueue();
        queueManager->addToStore(pAttender);
        //std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));
    }
    void addToAudienciaFromStore()
    {
        for(int i = 0; i < queueManager->getStore()->size(); i++){
            AttenderGroup* grupo = queueManager->getStore()->at(i).takeFromWaitingQueue();
            queueManager->getAudienceArea()->addToWaitingQueue(grupo);
            //std::this_thread::sleep_for(std::chrono::seconds(velocidadSalidaSort));
        }   
    }
};