#include <iostream>
#include <fstream>
#include <thread>
#include "json.hpp"
#include "jsonManager.h"
#include "modelo/ConcertEntrance.h"

using namespace std;
using json = nlohmann::json;

class EntranceManager
{
private:
    int maxPersonas;
    int minPersonas;
    int cantidadDePersonas;
    int cantidadColasDeEntradas;
    int personasPorGrupo;
    int cantidadDeAttenderGroup;
    float velocidadEntrada;
    vector<ConcertEntrance*> *entrada;

public:
    EntranceManager()
    {
        entrada = new vector<ConcertEntrance*>;
        Config* config = new Config("config.json");

        maxPersonas = config->maxPersonasEnEntrada;
        minPersonas = config->minPersonasEnEntrada;
        velocidadEntrada = config->velocidadEntrada;
        cantidadColasDeEntradas = config->cantidadDeColasEntrada;
        personasPorGrupo = config->personasPorEntrada;

        cantidadDePersonas = rand() % (maxPersonas - minPersonas + 1) + minPersonas;

        int ocupacion = (cantidadDePersonas / cantidadColasDeEntradas)+10;

        for (int i = 0; i < cantidadColasDeEntradas; i++)
        {
            entrada->push_back(new ConcertEntrance(ocupacion));
        }
    }

    void addToEntrance()//debe ser un hilo con tiempo de espera sacado del json
    {
        while (cantidadDePersonas > 0)
        {
            for (int j = 0; j < cantidadColasDeEntradas && cantidadDePersonas > 0; j++)
            {

                entrada->at(j)->addToWaitingQueue(new AttenderGroup(personasPorGrupo));
                cantidadDeAttenderGroup++;
                // std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));
                cantidadDePersonas-=personasPorGrupo;
                
            }
        }
    }

    vector<ConcertEntrance*> *getEntrance()
    {
        return entrada;
    }

    int getCantidadDePersonas()
    {
        return cantidadDePersonas;
    }
    int cantidadDeAttenderGroup()
    {
        return cantidadDeAttenderGroup;
    }
};