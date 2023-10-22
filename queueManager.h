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
    vector<Store *> *tiendas;
    vector<Bathroom *> *bannos;
    AudienceArea *audiencia;

public:
    QueueManager(int pCantidadDeGrupos)
    {
        tiendas = new vector<Store *>;
        bannos = new vector<Bathroom *>;
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
        thread BTA = thread(&QueueManager::bathToAudiencia,this);
        thread STA = thread(&QueueManager::storeToAudiencia,this);
    }

    void addQTBAux(int pQuantity)
    {

        thread addQTB = thread(&QueueManager::addQuantityToBath, this, pQuantity);
        addQTB.join(); // Esperar a que el hilo addQTB termine
        return;
    }
    void addQTSAux(int pQuantity){
        thread addQTS = thread(&QueueManager::addQuantityToStore, this, pQuantity);
        addQTS.join(); // Esperar a que el hilo addQTS termine
        return;
    }
    void addQTAAux(int pQuantity){
        thread addQTA = thread(&QueueManager::addQuantityToAudiencia, this, pQuantity);
        addQTA.join(); // Esperar a que el hilo addQTA termine
        return;
    }

    void addQuantityToBath(int pQuantity) // deber ser un hilo con tiempo de espera sacado del json
    {
        while (true){
            for (int i = 0; i < cantidadDeBannos; i++)
            {
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
                if (pQuantity - personasPromedioPorGrupo < 0)
                {
                    bannos->at(i)->addToWaitingQueue(new AttenderGroup(pQuantity));
                    cout << "Agregando a bannos "<<pQuantity<<" personas"  << endl;
                    break;
                }
                bannos->at(i)->addToWaitingQueue(new AttenderGroup(personasPromedioPorGrupo));
                cout << "Agregando a bannos "<<personasPromedioPorGrupo<<" personas"  << endl;
                pQuantity -= personasPromedioPorGrupo;
            }
        }
    }

    void addQuantityToStore(int pQuantity) // deber ser un hilo con tiempo de espera sacado del json
    {
        while (true){
            for (int i = 0; i < cantidadDeStore; i++)
            {
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
                if (pQuantity - personasPromedioPorGrupo < 0)
                {
                    tiendas->at(i)->addToWaitingQueue(new AttenderGroup(pQuantity));
                    cout << "Agregando a tiendas "<<pQuantity<<" personas"  << endl;
                    break;
                }
                tiendas->at(i)->addToWaitingQueue(new AttenderGroup(personasPromedioPorGrupo));
                cout << "Agregando a tiendas "<<personasPromedioPorGrupo<<" personas"  << endl;
                pQuantity -= personasPromedioPorGrupo;
            }
        }
    }

    void addQuantityToAudiencia(int quantity) // deber ser un hilo con tiempo de espera sacado del json
    {
        while (true){
            thread addQTA = thread(&QueueManager::addQuantityToAudiencia, this, quantity);

            for (int i = 0; i < quantity; i++)
            {
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
                if (quantity - personasPromedioPorGrupo < 0)
                {
                    audiencia->addToWaitingStack(new AttenderGroup(quantity));
                    cout << "Agregando a audiencia "<<quantity<<" personas"  << endl;
                    break;
                }
                audiencia->addToWaitingStack(new AttenderGroup(personasPromedioPorGrupo));
                cout << "Agregando a audiencia "<<personasPromedioPorGrupo<<" personas"  << endl;
                quantity -= personasPromedioPorGrupo;
            }
        }
    }

    void bathToAudiencia() // deber ser un hilo con tiempo de espera sacado del json
    {
        while (true){
            cout << "Thread BTA"  << endl;
            for (int i = 0; i < bannos->size(); i++)
            {
                if(bannos->at(i)->getWaitingQueue()->getSize() == 0)
                {
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
                AttenderGroup *grupo = bannos->at(i)->takeFromWaitingQueue();
                cout << "se sacaron "<<grupo->getSize()<<" personas de Banno"  << endl;
                audiencia->addToWaitingStack(grupo);
            }
        }
    }

    void storeToAudiencia() // deber ser un hilo con tiempo de espera sacado del json
    {
        while (true){
            cout << "Thread STA"  << endl;
            for (int i = 0; i < tiendas->size(); i++)
            {
                if(tiendas->at(i)->getWaitingQueue()->getSize() == 0)
                {
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
                AttenderGroup *grupo = tiendas->at(i)->takeFromWaitingQueue();
                cout << "se sacaron "<<grupo->getSize()<<" personas de tienda"  << endl;
                audiencia->addToWaitingStack(grupo);
            }
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