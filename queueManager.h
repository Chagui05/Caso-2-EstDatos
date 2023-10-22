#include <iostream>
#include <fstream>
#include <thread>
#include "jsonManager.h"
#include "modelo/Store.h"
#include "modelo/Bathroom.h"
#include "modelo/AudienceArea.h"
#include "modelo/attender.h"

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
    int personasPromedioPorGrupo;
    float velocidadEntrada;
    vector<Store*> *tiendas;
    vector<Bathroom*> *bannos;
    AudienceArea *audiencia;

public:
    QueueManager(int pCantidadDeGrupos)
    {
        tiendas = new vector<Store*>;
        bannos = new vector<Bathroom*>;
        audiencia = new AudienceArea(pCantidadDeGrupos);
        cantidadDeGrupos = pCantidadDeGrupos;
        maxGrupos = pCantidadDeGrupos;

        Config config = Config("config.json");
        cantidadDeBannos = config.cantidadDeBannos;
        cantidadDeStore = config.cantidadDeStore;
        velocidadEntrada = config.velocidadEntrada;
        cantidadDeProductos = config.cantidadDeProductos;
        personasPromedioPorGrupo = config.personasPorEntrada;

        for (int i = 0; i < cantidadDeStore; i++)
        {
            tiendas->push_back(new Store(cantidadDeProductos));
        }
        for (int i = 0; i < cantidadDeBannos; i++)
        {
            bannos->push_back(new Bathroom());
        }
        thread BTA= thread(&QueueManager::bathToAudiencia,this);
        thread STA= thread(&QueueManager::storeToAudiencia,this);
    }

   void addQuantityToBath(int pQuantity)//deber ser un hilo con tiempo de espera sacado del json
    {
        thread addQTB= thread(&QueueManager::addQuantityToBath,this, pQuantity);
        for(int i = 0; i < cantidadDeBannos; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            if (pQuantity - personasPromedioPorGrupo < 0)
            {
                bannos->at(i)->addToWaitingQueue(new AttenderGroup(pQuantity));
                break;
            }
            bannos->at(i)->addToWaitingQueue(new AttenderGroup(personasPromedioPorGrupo));
            pQuantity -= personasPromedioPorGrupo;

        }
    }

   void addQuantityToStore(int pQuantity)//deber ser un hilo con tiempo de espera sacado del json
    {
        thread addQTS= thread(&QueueManager::addQuantityToStore,this, pQuantity);

        for(int i = 0; i < cantidadDeStore; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            if (pQuantity - personasPromedioPorGrupo < 0)
            {
                tiendas->at(i)->addToWaitingQueue(new AttenderGroup(pQuantity));
                break;
            }
            tiendas->at(i)->addToWaitingQueue(new AttenderGroup(personasPromedioPorGrupo));
            pQuantity -= personasPromedioPorGrupo;

        }
    }

    void addQuantityToAudiencia(int quantity)//deber ser un hilo con tiempo de espera sacado del json
    {
        thread addQTA= thread(&QueueManager::addQuantityToAudiencia,this, quantity);

        for (int i = 0; i < quantity; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            if (quantity - personasPromedioPorGrupo < 0)
            {
                audiencia->addToWaitingStack(new AttenderGroup(quantity));
                break;
            }
            audiencia->addToWaitingStack(new AttenderGroup(personasPromedioPorGrupo));
            quantity -= personasPromedioPorGrupo;
        }
    }

    void bathToAudiencia()//deber ser un hilo con tiempo de espera sacado del json
    {
        for (int i = 0; i < bannos->size(); i++)
        {
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            AttenderGroup *grupo = bannos->at(i)->takeFromWaitingQueue();
            audiencia->addToWaitingStack(grupo);
        }
    }

    void storeToAudiencia()//deber ser un hilo con tiempo de espera sacado del json
    {
        for (int i = 0; i < tiendas->size(); i++)
        {
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            AttenderGroup *grupo = tiendas->at(i)->takeFromWaitingQueue();
            audiencia->addToWaitingStack(grupo);
        }
    }
    
    vector<Store *> *getStore()
    {
        return tiendas;
    }
    vector<Bathroom *> *getBathroom()
    {
        return bannos;
    }
    AudienceArea *getAudienceArea()
    {
        return audiencia;
    }
};