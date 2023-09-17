//Clase para manejar el stage/gramilla, contienen un id, si esta ocupado o no y la cantidad de ellos que hay

#ifndef _STAGE_
#define _STAGE_ 1
#include <string>
#include <thread>

class Stage {
private: 
    bool isFull;
    
public:
    Stage(){
        bool isFull = false;
    }
    void setFull{
        isFull=true;
    }
    bool getFull{
        return isFull;
    }
    
};

#endif