#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
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
    }

    void addQTBAux(int pQuantity)
    {
        thread addQTB = thread(&QueueManager::addQuantityToBath, this, pQuantity);
        addQTB.join(); // Esperar a que el hilo addQTB termine
        return;
    }
    void addQTSAux(int pQuantity)
    {
        thread addQTS = thread(&QueueManager::addQuantityToStore, this, pQuantity);
        addQTS.join(); // Esperar a que el hilo addQTS termine
        return;
    }
    void addQTAAux(int pQuantity)
    {
        thread addQTA = thread(&QueueManager::addQuantityToAudiencia, this, pQuantity);
        addQTA.join(); // Esperar a que el hilo addQTA termine
        return;
    }

    void threadsConWhileTrue()
    {
        // thread bath = thread(&QueueManager::bathToAudiencia);
        // thread store = thread(&QueueManager::storeToAudiencia);
        std::thread bath(std::bind(&QueueManager::bathToAudiencia, this));
        std::thread store(std::bind(&QueueManager::storeToAudiencia, this));
        bath.join();
        store.join();
        return;
    }


    void addQuantityToBath(int pQuantity) // deber ser un hilo con tiempo de espera sacado del json
    {
        for (int i = 0; i < cantidadDeBannos; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            if (pQuantity - personasPromedioPorGrupo < 0)
            {
                bannos->at(i)->addToWaitingQueue(new AttenderGroup(pQuantity));
                cout << "Agregando a bannos " << pQuantity << " personas" << endl;
                break;
            }
            bannos->at(i)->addToWaitingQueue(new AttenderGroup(personasPromedioPorGrupo));
            cout << "Agregando a bannos " << personasPromedioPorGrupo << " personas" << endl;
            pQuantity -= personasPromedioPorGrupo;
        }
    }

    void addQuantityToStore(int pQuantity) // deber ser un hilo con tiempo de espera sacado del json
    {
        for (int i = 0; i < cantidadDeStore; i++)
        {
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            if (pQuantity - personasPromedioPorGrupo < 0)
            {
                tiendas->at(i)->addToWaitingQueue(new AttenderGroup(pQuantity));
                cout << "Agregando a tiendas " << pQuantity << " personas" << endl;
                break;
            }
            tiendas->at(i)->addToWaitingQueue(new AttenderGroup(personasPromedioPorGrupo));
            cout << "Agregando a tiendas " << personasPromedioPorGrupo << " personas" << endl;
            pQuantity -= personasPromedioPorGrupo;
        }
    }

    void addQuantityToAudiencia(int quantity) // deber ser un hilo con tiempo de espera sacado del json
    {

        for (int i = 0; quantity > 0; i++)
        {
            cout<<endl;
            auto startTime = std::chrono::high_resolution_clock::now();
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
            if (quantity < personasPromedioPorGrupo && quantity > 0)
            {
                audiencia->addToWaitingStack(new AttenderGroup(quantity));
                cout << "Agregando a audiencia: " << quantity << " personas" << endl;
                cout << "Personas en audiencia: " << audiencia->getAttenderNum() << endl;
                auto endTime = std::chrono::high_resolution_clock::now();   
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                cout << "Time elapsed in the thread: " << duration.count() << " ms" << std::endl;
                break;
            }
            audiencia->addToWaitingStack(new AttenderGroup(personasPromedioPorGrupo));
            cout << "Agregando a audiencia " << personasPromedioPorGrupo << " personas" << endl;
            cout << "Personas en audiencia: " << audiencia->getAttenderNum() << endl;
            quantity -= personasPromedioPorGrupo;
            auto endTime = std::chrono::high_resolution_clock::now();   
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            cout << "Tiempo promedio en el hilo: " << duration.count() << " ms" << std::endl;
        }
    }

    void bathToAudiencia() // deber ser un hilo con tiempo de espera sacado del json
    {
        cout << "entro a Thread BTA" << endl;
        while (true&& !bannosVacios())
        {
            cout << "Thread BTA" << endl;
            for (int i = 0; i < bannos->size(); i++)
            {
                if (bannos->at(i)->getWaitingQueue()->getSize() == 0)
                {
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
                AttenderGroup *grupo = bannos->at(i)->takeFromWaitingQueue();
                cout << "se sacaron " << (grupo->getSize()) << " personas de Banno" << endl;
                audiencia->addToWaitingStack(grupo);
            }
        }
    }

    void storeToAudiencia() // deber ser un hilo con tiempo de espera sacado del json
    {
        cout << "entro a Thread sTA" << endl;
        while (true && !tiendaVacia())
        {
            cout << "Thread STA" << endl;
            for (int i = 0; i < tiendas->size(); i++)
            {
                if (tiendas->at(i)->getWaitingQueue()->getSize() == 0)
                {
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(static_cast<int>(velocidadEntrada * 1000)));
                cout << "Trabajando" << endl;
                AttenderGroup *grupo = tiendas->at(i)->takeFromWaitingQueue();
               
                cout << (nullptr == grupo) << endl;
                audiencia->addToWaitingStack(grupo);
            }
        }
    }

    bool tiendaVacia()
    {
        for (int i = 0; i < tiendas->size(); i++)
        {
            if (tiendas->at(i)->getWaitingQueue()->getSize() != 0)
            {
                return false;
            }
        }
        return true;
    }
    
    bool bannosVacios()
    {
        for (int i = 0; i < bannos->size(); i++)
        {
            if (bannos->at(i)->getWaitingQueue()->getSize() != 0)
            {
                return false;
            }
        }
        return true;
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