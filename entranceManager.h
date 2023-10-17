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
    float velocidadEntrada;
    vector<ConcertEntrance> *entrada;

public:
    EntranceManager()
    {
        entrada = new vector<ConcertEntrance>;
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
            entrada->push_back(ConcertEntrance(ocupacion));
        }
    }

    // será un hilo
    void addToEntrance()
    {
        while (cantidadDePersonas > 0)
        {
            for (int j = 0; j < cantidadColasDeEntradas && cantidadDePersonas > 0; j++)
            {

                entrada->at(j).addToWaitingQueue(new AttenderGroup(personasPorGrupo));
                // std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));
                cantidadDePersonas-=personasPorGrupo;
            }
        }
    }

    vector<ConcertEntrance> *getEntrance()
    {
        return entrada;
    }

    int getCantidadDePersonas()
    {
        return cantidadDePersonas;
    }
};