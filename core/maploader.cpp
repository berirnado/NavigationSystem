#include "maploader.h"
#include <fstream>
#include <iostream>
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

MapLoader::MapLoader(string filePath) {};

void MapLoader::loadEdges(Grafo& grafo){
    //Testes de leitura JSON
    std::ifstream f("data\\edges.json");
    if (!f.is_open()) {
        std::cerr << "ERRO: erro ao abrir arquivo edges.json\n";
    }
    json data = json::parse(f);

    //itera sobre cada objeto do json
    int i = 0;
    for (const auto& aresta : data) {
        long u = aresta["u"];
        long v = aresta["v"];
        auto& dadosAresta = aresta["data"];
        double peso = dadosAresta["length"];
        bool isOneWay = dadosAresta["oneway"];

        grafo.addAresta(u, v, peso, isOneWay);
    }
}

