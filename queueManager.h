#include <iostream>
#include <fstream>
#include <thread>
#include "jsonManager.h"
#include "Store.h"
#include "Bathroom.h"
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
    }

    void addQuantityToBath(int pQuantity)//deber ser un hilo con tiempo de espera sacado del json
    {
        for(int i = 0; i < cantidadDeBannos; i++)
        {
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
        for(int i = 0; i < cantidadDeStore; i++)
        {
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
        for (int i = 0; i < quantity; i++)
        {
            if (quantity - personasPromedioPorGrupo < 0)
            {
                audiencia->addToWaitingStack(new AttenderGroup(quantity));
                break;
            }
            audiencia->addToWaitingStack(new AttenderGroup(personasPromedioPorGrupo));
            quantity -= personasPromedioPorGrupo;
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