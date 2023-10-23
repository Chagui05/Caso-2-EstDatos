#include "EntranceManager.h"
#include "SortEntranceManager.h"
#include <iostream>
#include <thread>

int main (){
    EntranceManager* entrada = new EntranceManager();

    SortManager* sorter = new SortManager(entrada->getCantidadDePersonas(), entrada->getCantidadDeAttenderGroup());

    sorter->sortToBathStoreOrAudience(); 

    std::this_thread::sleep_for(std::chrono::milliseconds(6000));


    cout <<"Personas en audienceArea: " << sorter->getQueueManager()->getAudienceArea()->getAttenderNum() <<endl;
    cout << "Personas en bathroom: "<< sorter->getQueueManager()->getBathroom()->at(1)->getWaitingQueue()->getSize()<<endl;
    cout << "Personas en store: "<< sorter->getQueueManager()->getStore()->at(1)->getAttenderNum()<<endl;
    cout <<sorter->getQueueManager()->tiendaVacia()<<endl;

   sorter->getQueueManager()->threadsConWhileTrue();

   
}

//?g++ -std=c++11 -o main main.cpp -lpthread