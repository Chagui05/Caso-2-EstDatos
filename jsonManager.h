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
    double posibilidadGramilla;
    double posibilidadBanno;
    double posibilidadTienda;
    std::vector<std::pair<std::string, double>> timeAtPlace; //Vector con el lugar y el tiempo
    std::vector<std::tuple<double, std::string, int, double>> eventos; //Vector con una tupla con evento, tiempo en el evento, orden del evento y los eventos
};

Config loadConfig(string configFile) {

    // Leer el JSON desde un archivo
    std::ifstream jsonFile(configFile);
    json jsonData;
    jsonFile >> jsonData;

    // Crear una instancia de la estructura Config
    Config config;

    // Asignar los valores del JSON a la estructura Config
    config.maxPersonasEnEntrada = jsonData["rangosEntrada"]["maxPersonasEnEntrada"];
    config.minPersonasEnEntrada = jsonData["rangosEntrada"]["minPersonasEnEntrada"];
    config.velocidadEntrada = jsonData["rangosEntrada"]["velocidadEntrada"];
    config.velocidadSalidaSort = jsonData["rangosEntrada"]["velocidadSalidaSort"];
    config.cantidadDeBannos = jsonData["cantidadDeBannos"];
    config.cantidadDeCubiculos = jsonData["cantidadDeCubiculos"];
    config.cantidadDeStore = jsonData["cantidadDeStore"];
    config.cantidadDeCajeros = jsonData["cantidadDeCajeros"];
    config.cantidadDeProductos = jsonData["cantidadDeProductos"];
    config.cantidadDeColasEntrada = jsonData["canitdadDeColasDeEntrada"];
    config.posibilidadGramilla = jsonData["probabilidades"]["entrada"]["posibilidadGramilla"];
    config.posibilidadBanno = jsonData["probabilidades"]["entrada"]["posibilidadBanno"];
    config.posibilidadTienda = jsonData["probabilidades"]["entrada"]["posibilidadTienda"];

    for (const auto& entry : jsonData["timeAtPlace"]) {
        std::string place = entry["place"];
        double time = entry["time"];
        config.timeAtPlace.push_back(std::make_pair(place, time));
    }

    for (const auto& evento : jsonData["eventos"]) {
        double time = evento["time"];
        std::string event_type = evento["event_type"];
        int orderID = evento["orderID"];
        
        if (evento.find("eventos_dentro") != evento.end()) {
            for (const auto& evento_dentro : evento["eventos_dentro"]) {
                if (evento_dentro.find("irAlBanno") != evento_dentro.end()) {
                    double irAlBanno = evento_dentro["irAlBanno"];
                    config.eventos.push_back(std::make_tuple(time, event_type, orderID, irAlBanno));
                }
                if (evento_dentro.find("comprarComida") != evento_dentro.end()) {
                    double comprarComida = evento_dentro["comprarComida"];
                    config.eventos.push_back(std::make_tuple(time, event_type, orderID, comprarComida));
                }
                if (evento_dentro.find("salir") != evento_dentro.end()) {
                    double salir = evento_dentro["salir"];
                    config.eventos.push_back(std::make_tuple(time, event_type, orderID, salir));
                }
            }
        } else {
            config.eventos.push_back(std::make_tuple(time, event_type, orderID, 0.0));
        }
    }

    return config;
}
