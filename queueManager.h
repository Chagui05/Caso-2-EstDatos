#include <iostream>
#include <fstream>
#include <thread>
#include "json.hpp"
#include "jsonManager.h"
#include "Store.h"
#include  "Bathroom.h"
#include "AudienceArea.h"
#include "attender.h"

using namespace std;
using json = nlohmann::json;

class QueueManager
{
private:

    int cantidadDeBannos;
    int cantidadDeStore;
    int cantidadDeProductos;
    int cantidadDeGrupos;
    int maxGrupos;
    float velocidadEntrada;
    vector<Store>* tiendas;
    vector<Bathroom>* bannos;
    AudienceArea* audiencia;


public:

    QueueManager(int pCantidadDeGrupos)
    {
        tiendas = new vector<Store>;
        bannos = new vector<Bathroom>;
        audiencia = new AudienceArea(pCantidadDeGrupos);
        cantidadDeGrupos = pCantidadDeGrupos;
        maxGrupos = pCantidadDeGrupos;

        Config config = loadConfig("config.json");
        cantidadDeBannos = config.cantidadDeBannos;
        cantidadDeStore = config.cantidadDeStore;
        velocidadEntrada = config.velocidadEntrada;
        cantidadDeProductos = config.cantidadDeProductos;

        for (int i = 0 ; i < cantidadDeStore; i++){
            tiendas->push_back(Store(cantidadDeProductos));
        }
        for (int i = 0 ; i < cantidadDeBannos; i++){
            bannos->push_back(Bathroom());
        }    
    }

    // será un hilo
    void addToBath(AttenderGroup* pAttender)
    {
        while(cantidadDeGrupos > 0){
            for (int j = 0; j < cantidadDeStore && cantidadDeGrupos > 0; j++){
                bannos->at(j).addToWaitingQueue(pAttender);
                cantidadDeGrupos--;
            }
        }
    }

    void addToStore(AttenderGroup* pAttender)
    {
        while(cantidadDeGrupos > 0){
            for (int j = 0; j < cantidadDeBannos && cantidadDeGrupos > 0; j++){
                tiendas->at(j).addToStoreQueue(pAttender);
                cantidadDeGrupos--;
            }
        }
    }

    vector<Store>* getStore(){
        return tiendas;
    }
    vector<Bathroom>* getBathroom(){
        return bannos;
    }
    AudienceArea* getAudienceArea(){
        return audiencia;
    }

};