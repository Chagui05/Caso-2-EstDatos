#include <iostream>
#include <fstream>
#include <thread>
#include "json.hpp"
#include "ConcertEntrance.h"

using namespace std;
using json = nlohmann::json;

class entranceManager
{
private:

    int maxPersonas;
    int minPersonas;
    int cantidadDePersonas;
    int cantidadDeEntradas;
    float velocidadEntrada;
    vector<ConcertEntrance>* entrada;

public:

    entranceManager(){
        entrada = new vector<ConcertEntrance>;

        std::ifstream jsonFile("config.json");
        json jsonData;
        jsonFile >> jsonData;

        maxPersonas = jsonData["rangosEntrada"]["maxPersonasEnEntrada"];
        minPersonas = jsonData["rangosEntrada"]["minPersonasEnEntrada"];
        cantidadDeEntradas = jsonData["canitdadDeColasDeEntrada"];

        cantidadDePersonas = rand() % (maxPersonas - minPersonas + 1) + minPersonas;

        for (int i = 0 ; i < cantidadDeEntradas; i++){
            entrada->push_back(ConcertEntrance(cantidadDePersonas));
        }   
    }

};