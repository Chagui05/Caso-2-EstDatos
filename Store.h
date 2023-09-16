#ifndef _STORE_
#define _STORE_ 1
#include <string>
using namespace std;

class STORE {
private: 
    bool open;
    string storage
    
public:
    store(){
        open = false;
        storage = "FULL"
    }
    void setOpen(){
        open = true;
    }
    bool getOpen(){
        return open;
    }
    void setStorage(){
        if (storage == "FULL"){
            storage == "EMPTY"
        }
        else{
            storage == "FULL"
        }
    }
};

#endif