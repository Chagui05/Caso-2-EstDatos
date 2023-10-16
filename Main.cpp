#include "EntranceManager.h"
#include "SortEntranceManager.h"

int main (){
    
    EntranceManager* entrada = new EntranceManager();
    entrada->addToEntrance(); //crea personas en lista de espera

    SortEntranceManager* sortEntrance = new SortEntranceManager(entrada->getEntrance, entrada->);
}