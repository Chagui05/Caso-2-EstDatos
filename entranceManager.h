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
        cout<<"van a entrar: "<< cantidadDePersonas << " personas"<<endl;
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
