#ifndef _CONCERTENTRANCE_
#define _CONCERTENTRANCE_ 1
#include <string>
#include "listas/List.h"
#include "attender.h"
#include "waitingQueues.h"

using namespace std;

class ConcertEntrance : public waitingQueues {
private: 

    int spectatorsCount;

public:

    ConcertEntrance(int maxOcuppancy):waitingQueues(maxOcuppancy)
    {
        spectatorsCount = 0;
    }
    
};
#endif