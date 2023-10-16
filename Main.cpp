#include "EntranceManager.h"
#include "SortEntranceManager.h"

int main (){
    
    EntranceManager* entrada = new EntranceManager();
    entrada->addToEntrance(); //crea personas en lista de espera

    SortEntranceManager* sortEntrance = new SortEntranceManager(entrada->getEntrance, entrada->getCantidadDeGrupos);
    sortEntrance->sortToBathStoreAudience(); //crea subgrupos y los manda a los baños, tiendas y graderias
    
    // Segun el tiempo, ir agregndo a las personas desde bath y store a la audiencia



    return 0;
}