//Clase para manejar el stage/gramilla, contienen un id, si esta ocupado o no y la cantidad de ellos que hay

#ifndef _AUDIENCEAREA_
#define _AUDIENCEAREA_ 1
#include <string>
#include <thread>
#include "../listas/List.h"
#include "attender.h"

using namespace std;

class AudienceArea
{
private: 

    bool full;
    bool empty;
    int maxOccupancy;
    Stack<AttenderGroup> *wStack;

public:
        
    AudienceArea(int pMaxOccupancy)
    {
        full = false;
        empty = true;
        maxOccupancy = pMaxOccupancy;
        wStack = new List<AttenderGroup>();
    }

    
    void addToWaitingStack(AttenderGroup *attender)
    {
        if (full)
        {
            return;
        }
        empty = false;
        wStack->push(attender);
    }
    
    //hilo
    void addQuantityToWaitingStack(int quantity, int amountOfPEople)
    {
        if (full)
        {
            return;
        }
        empty = false;
        for (int i = 0; i < quantity; i++)
        {
            wStack->push(new AttenderGroup(amountOfPEople));
        }
    }

    AttenderGroup *takeFromWaitingStack()
    {
        if (!full)
        {
            return nullptr;
        }   
        return wStack->pop();
    }

    bool getFull()
    {
        return full;
    }

    void setFull()
    {
        full = true;
    }

    bool getEmpty()
    {
        return empty;
    }

    Stack<AttenderGroup>* getWaitingStack()
    {
        return wStack;
    }


};
#endif