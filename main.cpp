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

    // teste 1 ->grafos
    Grafo g;

    cout << " grafo com mock data " << endl;

    long long idCasa = 3492019482;
    long long idUfpel = 5529102231;
    long long idCentro = 9988776655;

    g.addAresta(idCasa, idUfpel, 500.0);
    g.addAresta(idUfpel, idCentro, 1200.5);
    g.addAresta(idCentro, idCasa, 1500.0);

    cout << "vertices inseridos: " << g.verticeCount() << endl;

    if (g.verticeCount() == 3) {
        cout << "[SUCESSO] o grafo mapeou os idss corretamente!" << endl;
    } else {
        cout << "[ERRO] algo deu errado na contagem do grafo." << endl;
    }
    cout << endl;

    // teste 2 -> trie e autocomplete
    cout << "trie / autocomplete" << endl;
    Trie trie;

    // inserindo dados de teste (nome da rua -> id de algum nó dela)
    trie.insert("Av. Bento Goncalves", 1001);
    trie.insert("Av. Brasil", 1002);
    trie.insert("Av. Duque de Caxias", 1003);
    trie.insert("Rua General Osorio", 1004);
    trie.insert("Rua General Neto", 1005);

    // testando busca por "Av. B"
    string busca = "Av. B";
    cout << "Digitando: '" << busca << "'..." << endl;

    vector<string> resultados = trie.autocomplete(busca);

    if (resultados.empty()) {
        cout << "[ERRO] nenhuma sugestao encontrada (esperava Av. Bento e Av. Brasil)" << endl;
    } else {
        for(const string& s : resultados) {
            cout << "sugestao encontrada: " << s << endl;
        }
        cout << "[SUCESSO] trie funcionando!" << endl;
    }

    // ==========================================================

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
