//Clase para manejar los bathrooms, contienen un id, si esta ocupado o no y la cantidad de ellos que hay

#ifndef _BATHROOM_
#define _BATHROOM_ 1
#include <string>
#include "listas/List.h"
#include "attender.h"
#include "waitingQueues.h"

using namespace std;

class Bathroom : public waitingQueues
{
private:
    int ID;
    int bathCOunt;
public:
    
    Bathroom():waitingQueues(50)
    {
        ID = 0;
        bathCOunt++;
    }

};

#endif