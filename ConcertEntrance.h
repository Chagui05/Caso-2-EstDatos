#ifndef _CONCERTENTRANCE_
#define _CONCERTENTRANCE_ 1
#include <string>
using namespace std;

class ConcertEntrance {
private: 
    bool full;
    int maxOccupancy;
    int spectatorsCount;
public:
    ConcertEntrance(){
        full = false;
        maxOccupancy = 1000;
        spectatorsCount = 0;
    }

    void addToConcert(){
        while( ;spectatorsCount <= maxOccupancy; spectatorsCount++ ){
        }
        full = true;
    }
    int getSpectatorCount(){
        return spectatorsCount;
    }
    int getFull(){
        return full;
    }
    
};
