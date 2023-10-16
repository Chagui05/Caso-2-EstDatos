#ifndef _EXITMANAGER_ 
#define _EXITMANAGER_ 1
#include <string>
#include <thread>
#include "listas/List.h"
#include "attender.h"
#include "AudienceArea.h"

using namespace std;

class exitManager
{
private:

    bool timeToExit;
    AudienceArea* audienciaASalir;
    int cantidadDeGrupos;

public:
    
        exitManager(AudienceArea* pAudienciaASalir)
        {
            timeToExit = false;
            audienciaASalir = pAudienciaASalir;
        }
    
        
        //hilo
        void exit()
        {
            if (timeToExit != true){
                return;
            }
            else{
                while (audienciaASalir->getEmpty() == false)
                {
                    for (int i = 0; i < audienciaASalir->getWaitingStack()->getSize(); i++)
                    {
                        audienciaASalir->takeFromWaitingStack();
                    }
                }
            }
        }

};

#endif