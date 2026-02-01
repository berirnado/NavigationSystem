#include <QApplication>
#include <QDebug>
#include "grafo.h"
#include "trie.h"
#include "mainwindow.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // inicializa as estruturas principais
    Grafo g;
    Trie trie;

    //  ids
    long long idBento = 1001;
    long long idDuque = 1002;
    long long idGenNeto = 1003;
    long long idBrasil = 1004;

    // configuração da trie - nome da Rua é o id do nó
    trie.insert("Av. Bento Goncalves", idBento);
    trie.insert("Av. Duque de Caxias", idDuque);
    trie.insert("Rua General Neto", idGenNeto);
    trie.insert("Av. Brasil", idBrasil);

    cout << "[SUCESSO] Ruas inseridas na Trie." << endl;

    // configuração das coordenadas

    g.setCoordenada(idBento, -31.7654, -52.3376);
    g.setCoordenada(idDuque, -31.7600, -52.3400);
    g.setCoordenada(idGenNeto, -31.7550, -52.3450);
    g.setCoordenada(idBrasil, -31.7400, -52.3500);

    // GRAFO
    g.addAresta(idBento, idDuque, 500.0);
    g.addAresta(idDuque, idBento, 500.0);

    g.addAresta(idDuque, idGenNeto, 800.0);
    g.addAresta(idGenNeto, idDuque, 800.0);

    g.addAresta(idBento, idBrasil, 2500.0);
    g.addAresta(idBrasil, idBento, 2500.0);

    cout << "[SUCESSO] Grafo e Coordenadas configurados. Vertices: " << g.verticeCount() << endl;

    // ==========================================================
    //
    /*
    std::ifstream f("data/edges.json"); // Cuidado com a barra no Windows (use / ou \\)
    if (!f.is_open()) {
        std::cerr << "ERRO: arquivo nao abriu (verifique o caminho)\n";
    } else {
        json data = json::parse(f);

        for (const auto &aresta : data) {
            long long u = aresta["u"];
            long long v = aresta["v"];
            auto &dadosAresta = aresta["data"];
            double peso = dadosAresta["length"];
            bool isOneWay = dadosAresta["oneway"];

            // Importante: Ao ler do JSON, você também precisaria ler
            // um nodes.csv para dar g.setCoordenada(u, lat, lon)
            g.addAresta(u, v, peso);

            if (!isOneWay) {
                g.addAresta(v, u, peso);
            }
        }
        cout << "Leitura do JSON concluida. Total vertices: " << g.verticeCount() << endl;
    }
    */
    // ==========================================================

    // inicializa a Janela Principal
    MainWindow w;

    // passa os ponteiros do grafo e trie preenchidos pra ui
    w.setGrafo(&g);
    w.setTrie(&trie);

    w.show();

    return a.exec();
}
