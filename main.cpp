#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "grafo.h" // Sua classe nova

// Mantemos as bibliotecas do JSON para usar no futuro
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // TESTE - antes de ler o arquivo gigante, testando se o grafo aguenta IDs grandes

    Grafo g; // Note: Não precisa mais passar tamanho (ex: g(10))

    cout << "--- INICIANDO TESTE MANUAL (MOCK DATA) ---" << endl;

    // IDs gigantes simulando o OpenStreetMap
    long long idCasa = 3492019482;
    long long idUfpel = 5529102231;
    long long idCentro = 9988776655;

    // adiciona arestas manuais
    g.addAresta(idCasa, idUfpel, 500.0);
    g.addAresta(idUfpel, idCentro, 1200.5);
    g.addAresta(idCentro, idCasa, 1500.0);

    // verificacao
    cout << "Vertices inseridos: " << g.verticeCount() << endl;

    if (g.verticeCount() == 3) {
        cout << "[SUCESSO] O Grafo mapeou os IDs gigantes corretamente!" << endl;
    } else {
        cout << "[ERRO] Algo deu errado na contagem." << endl;
    }

    // --- LEITURA DO JSON (DESCOMENTAR DEPOIS) ---
    // quando o teste funcionar descomenta

    /*
    std::ifstream f("C:\\Users\\bernardo.robaina\\Documents\\UFPel\\c\\AED2\\sistema-navegacao\\data\\edges.json");
    if (!f.is_open()) {
        std::cerr << "ERRO: arquivo nao abriu (verifique o caminho)\n";
    } else {
        json data = json::parse(f);

        for (const auto &aresta : data) {
            // ATENCAO: Mudei de 'long' para 'long long' por causa do OSM
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

    // abre a janela do Qt (vai abrir em branco, olhe o terminal para ver o resultado do teste)
    MainWindow w;
    w.show();
    return a.exec();
}
