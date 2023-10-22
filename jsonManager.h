#ifndef _JSONMANAGER_
#define _JSONMANAGER_ 1

#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

// Define una estructura para almacenar la configuración
struct Config {
    int maxPersonasEnEntrada;
    int minPersonasEnEntrada;
    double velocidadEntrada;
    double velocidadSalidaSort;
    int cantidadDeBannos;
    int cantidadDeCubiculos;
    int cantidadDeStore;
    int cantidadDeCajeros;
    int cantidadDeProductos;
    int cantidadDeColasEntrada;
    int personasPorEntrada;
    double posibilidadGramilla;
    double posibilidadBanno;
    double posibilidadTienda;
    vector<pair<std::string, double>> timeAtPlace; //Vector con el lugar y el tiempo
    vector<tuple<double, std::string, int, double>> eventos; //Vector con una tupla con evento, tiempo en el evento, orden del evento y los eventos



Config (std::string configFile) {

    // Leer el JSON desde un archivo
    
    std::ifstream jsonFile(configFile);
    json jsonData;
    jsonFile >> jsonData;

    // Asignar los valores del JSON a la estructura Config
    maxPersonasEnEntrada = jsonData["rangosEntrada"]["maxPersonasEnEntrada"];
    minPersonasEnEntrada = jsonData["rangosEntrada"]["minPersonasEnEntrada"];
    personasPorEntrada = jsonData["rangosEntrada"]["personasPorEntrada"];
    velocidadEntrada = jsonData["rangosEntrada"]["velocidadEntrada"];
    velocidadSalidaSort = jsonData["rangosEntrada"]["velocidadSalidaSort"];
    cantidadDeBannos = jsonData["cantidadDeBannos"];
    cantidadDeCubiculos = jsonData["cantidadDeCubiculos"];
    cantidadDeStore = jsonData["cantidadDeStore"];
    cantidadDeCajeros = jsonData["cantidadDeCajeros"];
    cantidadDeProductos = jsonData["cantidadDeProductos"];
    cantidadDeColasEntrada = jsonData["canitdadDeColasDeEntrada"];
    posibilidadGramilla = jsonData["probabilidades"]["entrada"]["posibilidadGramilla"];
    posibilidadBanno = jsonData["probabilidades"]["entrada"]["posibilidadBanno"];
    posibilidadTienda = jsonData["probabilidades"]["entrada"]["posibilidadTienda"];
  

    for (const auto& entry : jsonData["timeAtPlace"]) {
        std::string place = entry["place"];
        double time = entry["time"];
        timeAtPlace.push_back(std::make_pair(place, time));
    }

    for (const auto& evento : jsonData["eventos"]) {
        double time = evento["time"];
        std::string event_type = evento["event_type"];
        int orderID = evento["orderID"];
        
        if (evento.find("eventos_dentro") != evento.end()) {
            for (const auto& evento_dentro : evento["eventos_dentro"]) {
                if (evento_dentro.find("irAlBanno") != evento_dentro.end()) {
                    double irAlBanno = evento_dentro["irAlBanno"];
                    eventos.push_back(std::make_tuple(time, event_type, orderID, irAlBanno));
                }
                if (evento_dentro.find("comprarComida") != evento_dentro.end()) {
                    double comprarComida = evento_dentro["comprarComida"];
                    eventos.push_back(std::make_tuple(time, event_type, orderID, comprarComida));
                }
                if (evento_dentro.find("salir") != evento_dentro.end()) {
                    double salir = evento_dentro["salir"];
                    eventos.push_back(std::make_tuple(time, event_type, orderID, salir));
                }
            }
        } else {
            eventos.push_back(std::make_tuple(time, event_type, orderID, 0.0));
        }
    }
}


};



#endif