#ifndef _CONCERTENTRANCE_
#define _CONCERTENTRANCE_ 1
#include <string>
#include "../listas/List.h"
#include "attender.h"
#include "waitingQueues.h"

using namespace std;

class ConcertEntrance : public waitingQueue {
private: 

    int spectatorsCount;

public:

    ConcertEntrance(int maxOcuppancy):waitingQueue(maxOcuppancy)
    {
        spectatorsCount = 0;
    }

    
    
};
#endif