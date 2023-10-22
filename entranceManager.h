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
    vector<ConcertEntrance*> entrada;
    thread managerThread;

public:
    EntranceManager()
    {
        Config* config = new Config("config.json");

        maxPersonas = config->maxPersonasEnEntrada;
        minPersonas = config->minPersonasEnEntrada;
        velocidadEntrada = config->velocidadEntrada;
        cantidadColasDeEntradas = config->cantidadDeColasEntrada;
        personasPorGrupo = config->personasPorEntrada;

        cantidadDePersonas = rand() % (maxPersonas - minPersonas + 1) + minPersonas;

        int ocupacion = (cantidadDePersonas / cantidadColasDeEntradas) + 10;

        for (int i = 0; i < cantidadColasDeEntradas; i++)
        {
            entrada.push_back(new ConcertEntrance(ocupacion));
        }

        // Start the manager thread
        managerThread = thread(&EntranceManager::addToEntrance, this);
    }

    void addToEntrance()
    {
        while (cantidadDePersonas > 0)
        {
            this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            for (int i = 0; i < cantidadColasDeEntradas; i++)
            {
                if (cantidadDePersonas > 0)
                {
                    entrada[i]->addToWaitingQueue(new AttenderGroup(personasPorGrupo));
                    cantidadDeAttenderGroup++;
                    cantidadDePersonas -= personasPorGrupo;
                }
            }
        }
    }

    vector<ConcertEntrance*> getEntrance()
    {
        return entrada;
    }

    int getCantidadDePersonas()
    {
        return cantidadDePersonas;
    }

    int getCantidadDeAttenderGroup()
    {
        return cantidadDeAttenderGroup;
    }
};
