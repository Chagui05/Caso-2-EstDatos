#ifndef _EXITMANAGER_ 
#define _EXITMANAGER_ 1
#include <string>
#include <thread>
#include "listas/List.h"
#include "attender.h"

using namespace std;

class exitManager
{
private:

    bool timeToExit;
    Stack<AttenderGroup> *wStack;
    int cantidadDeGrupos;

public:
    
        exitManager()
        {
            timeToExit = false;
            wStack = new List<AttenderGroup>();
        }
    
        
        //hilo
        void exit()
        {
            if (timeToExit != true){
                return
            };
            else{
                while (AudienceArea.getEmpty()!=False)
                {
                    for (int i = 0; i < wStack->getSize(); i++)
                    {
                        wStack->pop();
                    }
                }
            }
        }

}

#endif