#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "grafo.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // TESTE - antes de ler o arquivo gigante, testando se o grafo aguenta IDs grandes

    Grafo g;

    cout << "--- teste manual com mock data ---" << endl;

    long long idCasa = 3492019482;
    long long idUfpel = 5529102231;
    long long idCentro = 9988776655;

    g.addAresta(idCasa, idUfpel, 500.0);
    g.addAresta(idUfpel, idCentro, 1200.5);
    g.addAresta(idCentro, idCasa, 1500.0);

    cout << "Vertices inseridos: " << g.verticeCount() << endl;

    if (g.verticeCount() == 3) {
        cout << "[SUCESSO] O Grafo mapeou os IDs gigantes corretamente!" << endl;
    } else {
        cout << "[ERRO] Algo deu errado na contagem." << endl;
    }

    /*
    std::ifstream f("data\\edges.json");
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

            g.addAresta(u, v, peso);

            if (!isOneWay) {
                g.addAresta(v, u, peso);
            }
        }
        cout << "Leitura do JSON concluida. Total vertices: " << g.verticeCount() << endl;
    }
    */
    MainWindow w;
    w.show();
    return a.exec();
}
