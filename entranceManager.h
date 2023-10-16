#include <iostream>
#include <fstream>
#include <thread>
#include "json.hpp"
#include "jsonManager.h"
#include "ConcertEntrance.h"

using namespace std;
using json = nlohmann::json;

class EntranceManager
{
private:

    int maxPersonas;
    int minPersonas;
    int cantidadDeGrupos;
    int cantidadColasDeEntradas;
    float velocidadEntrada;
    vector<ConcertEntrance>* entrada;

public:

    EntranceManager()
    {
        entrada = new vector<ConcertEntrance>;
        Config config = loadConfig("config.json");

        maxPersonas = config.maxPersonasEnEntrada;
        minPersonas = config.minPersonasEnEntrada;
        velocidadEntrada = config.velocidadEntrada;
        cantidadColasDeEntradas = config.cantidadDeColasEntrada;
        
        cantidadDeGrupos = rand() % (maxPersonas - minPersonas + 1) + minPersonas;

        for (int i = 0 ; i < cantidadColasDeEntradas; i++){
            entrada->push_back(ConcertEntrance(cantidadDeGrupos / cantidadColasDeEntradas));
        }   
    }

    // será un hilo
    void addToEntrance()
    {
        while(cantidadDeGrupos > 0){
            for (int j = 0; j < cantidadColasDeEntradas && cantidadDeGrupos > 0; j++){

                entrada->at(j).addToWaitingQueue(new AttenderGroup(50));
                //std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));  
                cantidadDeGrupos--;
            }
        }
    }

    vector<ConcertEntrance>* getEntrance(){
        return entrada;
    }

};