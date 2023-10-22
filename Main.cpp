#include "EntranceManager.h"
#include "SortEntranceManager.h"
#include <iostream>
#include <thread>

int main (){
    EntranceManager* entrada = new EntranceManager();

    SortManager* sorter = new SortManager(entrada->getCantidadDePersonas(), entrada->getCantidadDeAttenderGroup());

    sorter->sortToBathStoreOrAudience(); 

    std::this_thread::sleep_for(std::chrono::milliseconds(6000));


    cout << sorter->getQueueManager()->getAudienceArea()->getWaitingStack()->getSize() <<endl;
    cout << sorter->getQueueManager()->getBathroom()->at(1)->getWaitingQueue()->getSize()<<endl;
    cout << sorter->getQueueManager()->getStore()->at(1)->getWaitingQueue()->getSize()<<endl;
    cout <<sorter->getQueueManager()->tiendaVacia()<<endl;

   sorter->getQueueManager()->threadsConWhileTrue();

   
}