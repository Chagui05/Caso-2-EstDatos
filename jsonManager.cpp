//Comando para probar  g++ -std=c++11 -o manager.o jsonManager.cpp

#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

int main() {
    //Leer el JSON desde un archivo (asegúrate de tener el archivo "data.json" en el mismo directorio)
    std::ifstream jsonFile("config.json");
    json jsonData;
    jsonFile >> jsonData;

    // Acceder a los valores del JSON
    int maxPersonasEnEntrada = jsonData["rangosEntrada"]["maxPersonasEnEntrada"];
    int minPersonasEnEntrada = jsonData["rangosEntrada"]["minPersonasEnEntrada"];
    bool gramillaFull = jsonData["gramillaFull"];
    int cantidadDeBannos = jsonData["cantidadDeBannos"];

    // Acceder a los valores dentro de "probabilidades"
    double posibilidadGramilla = jsonData["probabilidades"]["entrada"]["posibilidadGramilla"];
    double posibilidadBaño = jsonData["probabilidades"]["entrada"]["posibilidadBaño"];
    double posibilidadTienda = jsonData["probabilidades"]["entrada"]["posibilidadTienda"];

    // Acceder a los valores dentro de "timeAtPlace"
    for (const auto& entry : jsonData["timeAtPlace"]) {
        std::string place = entry["place"];
        double time = entry["time"];
        std::cout << "Place: " << place << ", Time: " << time << std::endl;
    }

    // Acceder a los valores dentro de "eventos"
    for (const auto& evento : jsonData["eventos"]) {
        double time = evento["time"];
        std::string event_type = evento["event_type"];
        int orderID = evento["orderID"];
        
        if (evento.find("eventos_dentro") != evento.end()) {
            for (const auto& evento_dentro : evento["eventos_dentro"]) {
                if (evento_dentro.find("irAlBanno") != evento_dentro.end()) {
                    double irAlBanno = evento_dentro["irAlBanno"];
                    std::cout << "Time: " << time << ", Event Type: " << event_type << ", Order ID: " << orderID
                              << ", Ir al Baño: " << irAlBanno << std::endl;
                }
                if (evento_dentro.find("comprarComida") != evento_dentro.end()) {
                    double comprarComida = evento_dentro["comprarComida"];
                    std::cout << "Time: " << time << ", Event Type: " << event_type << ", Order ID: " << orderID
                              << ", Comprar Comida: " << comprarComida << std::endl;
                }
                if (evento_dentro.find("salir") != evento_dentro.end()) {
                    double salir = evento_dentro["salir"];
                    std::cout << "Time: " << time << ", Event Type: " << event_type << ", Order ID: " << orderID
                              << ", Salir: " << salir << std::endl;
                }
            }
        } else {
            std::cout << "Time: " << time << ", Event Type: " << event_type << ", Order ID: " << orderID << std::endl;
        }
    }

    return 0;
}
