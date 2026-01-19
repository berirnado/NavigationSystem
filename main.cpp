#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "grafo.h"

#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Testes da classe grafo
    // Grafo g(10);
    // g.addAresta(0, 1, 2.5);
    // g.addAresta(1, 2, 1.2);
    // g.addAresta(1, 0, 2.5);
    // g.addAresta(0, 2, 2.5);
    // g.addAresta(0, 3, 2.5);

    // qDebug() << "Vertices:" << g.verticeCount();
    // qDebug() << "Vizinhos do 0:" << g.vizinhos(0).size();

    //Testes de leitura JSON
    std::ifstream f("C:\\Users\\bernardo.robaina\\Documents\\UFPel\\c\\AED2\\sistema-navegacao\\data\\edges.json");
    if (!f.is_open()) {
        std::cerr << "ERRO: arquivo nao abriu\n";
        return 0;
    }
    json data = json::parse(f);

    auto numeroDeObjetosEuAcho = data.size();

    //itera sobre cada objeto do json
    int i = 0;
    for (const auto& aresta : data) {
        long u = aresta["u"];
        long v = aresta["v"];
        auto& dadosAresta = aresta["data"];
        double peso = dadosAresta["length"];
        bool isOneWay = dadosAresta["oneway"];

        // g.addAresta(u, v, peso);
        // if (!isOneWay) {
        //     // caso seja via dupla a aresta é bidirecional então adicionamos a
        //     // aresta com origem e destino invertidos
        //     g.addAresta(v, u, peso);
        // }
    }

    return a.exec();
}
