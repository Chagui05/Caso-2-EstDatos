#include <iostream>
#include <fstream>
#include <thread>
#include "json.hpp"
#include "jsonManager.h"
#include "ConcertEntrance.h"

using namespace std;
using json = nlohmann::json;

class entranceManager
{
private:

    int maxPersonas;
    int minPersonas;
    int cantidadDeGrupos;
    int cantidadColasDeEntradas;
    float velocidadEntrada;
    vector<ConcertEntrance>* entrada;

public:

    entranceManager(){
        entrada = new vector<ConcertEntrance>;

        Config config = loadConfig("config.json")

        maxPersonas = config.maxPersonasEntrada;
        minPersonas = config.minPersonasEnEntrada;
        velocidadEntrada = config.velocidadEntrada;
        cantidadColasDeEntradas = config.cantidadDeColasEntrada;
        
        cantidadDeGrupos = rand() % (maxPersonas - minPersonas + 1) + minPersonas;

        for (int i = 0 ; i < cantidadColasDeEntradas; i++){
            entrada->push_back(ConcertEntrance(cantidadDeGrupos / cantidadColasDeEntradas));
        }   
    }

    // será un hilo
    void addToEntrance(){
        while(cantidadDeGrupos > 0){
            for (int j = 0; j < cantidadColasDeEntradas; j++){

                entrada->at(j).addToWaitingQueue(new AttenderGroup());
                //std::this_thread::sleep_for(std::chrono::seconds(velocidadEntrada));  
                if(cantidadDeGrupos > 0 ){
                    cantidadDeGrupos--;
                }   
            }
        }
    }

};