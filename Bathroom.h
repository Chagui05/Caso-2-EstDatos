//Clase para manejar los bathrooms, contienen un id, si esta ocupado o no y la cantidad de ellos que hay

#ifndef _BATHROOM_
#define _BATHROOM_ 1
#include <string>
using namespace std;

class Bathroom {
private: 
    int ID;
    bool occupied;
    int countBaths;
    
public:
    Bathroom(){
        ID = 402+countBaths;
        occupied = false;
        countBaths++
    }
    void setOccupied(){
        occupied = true;
    }
    bool getOccupied(){
        return occupied;
    }
    int getID(){
        return ID;
    }
    
};

#endif