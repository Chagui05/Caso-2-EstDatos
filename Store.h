//Clase para el manejo de la tienda del concierto, contiene un booleano de si esta abierta o no y uno de si esta el almacenamiento lleno o no

#ifndef _STORE_
#define _STORE_ 1
#include <string>
#include "listas/List.h"
#include "attender.h"
#include "waitingQueues.h"

using namespace std;

class Store : public waitingQueues {
private: 

    int productCount;
    bool outOfStock;
    bool open;

public:

    Store(int pProducount):waitingQueues(50)
    {
        outOfStock = false;
        productCount = pProducount;
        open = true;

    }

    //Hilo de entrada
    void addToStoreQueue(AttenderGroup *attender)
    {
        if (open)
        {
            addToWaitingQueue(attender);   
        }
    }
    void takeFromStoreQueue()
    {
        if(productCount == 0 && !outOfStock)
        {
           outOfStock = true;
           return;
        }
        takeFromWaitingQueue();
        productCount--; // <-- eso hacerlo con vector pila luego 
    }

    void fillStore()
    {
        productCount = 50;
        outOfStock = false;
    }
    
};

#endif