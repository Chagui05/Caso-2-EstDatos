//Clase para el manejo de la tienda del concierto, contiene un booleano de si esta abierta o no y uno de si esta el almacenamiento lleno o no

#ifndef _STORE_
#define _STORE_ 1
#include <string>
using namespace std;

class STORE {
private: 
    bool open;
    bool storageFull
    
public:
    store(){
        open = false;
        storage = true
    }
    void setOpen(){
        open = true;
    }
    bool getOpen(){
        return open;
    }
    void setStorage(){
        storage = !storage 
    }
};

#endif