//Clase para manejar el stage/gramilla, contienen un id, si esta ocupado o no y la cantidad de ellos que hay

#ifndef _AUDIENCEAREA_
#define _AUDIENCEAREA_ 1
#include <string>
#include <thread>
#include "listas/List.h"
#include "attender.h"
#include "waitingQueues.h"

using namespace std;

class AudienceAre: public waitingQueues {
private: 
    
public:
       
    AudienceAre(int pMaxOccupancy):waitingQueues(pMaxOccupancy)
    {
    }
    
};

#endif