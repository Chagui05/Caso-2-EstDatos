#include "EntranceManager.h"
#include "SortEntranceManager.h"
#include <iostream>

int main (){
    EntranceManager* entrada = new EntranceManager();

    SortManager* sorter = new SortManager(entrada->getCantidadDePersonas(), entrada->getCantidadDeAttenderGroup());

    sorter->sortToBathStoreOrAudience(); 

    

    return 0;
}