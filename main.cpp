#include <QApplication>
#include <QDebug>
#include "grafo.h"
#include "trie.h"
#include "mainwindow.h"

#include "nlohmann/json.hpp" // Certifique-se que essa lib está inclusa
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Inicializa as estruturas principais
    Grafo g;
    Trie trie;

    cout << "--- INICIANDO CARREGAMENTO DA BASE DE DADOS (OSM) ---" << endl;

    ifstream fNodes("data/nodes.json");
    if (!fNodes.is_open()) {
        cerr << "[ERRO CRITICO] Nao foi possivel abrir data/nodes.json" << endl;
        return -1;
    }

    json jNodes;
    try {
        fNodes >> jNodes;
    } catch (const exception& e) {
        cerr << "[ERRO JSON] Falha ao ler nodes.json: " << e.what() << endl;
    }

    int countNodes = 0;
    for (const auto& node : jNodes) {
        // OSMNX
        if (node.contains("id") && node.contains("y") && node.contains("x")) {
            long long id = node["id"];
            double lat = node["y"];
            double lon = node["x"];

            g.setCoordenada(id, lat, lon);
            countNodes++;
        }
    }
    cout << "[OK] Nodos carregados: " << countNodes << endl;
    fNodes.close();



    ifstream fEdges("data/edges.json");
    if (!fEdges.is_open()) {
        cerr << "[ERRO CRITICO] Nao foi possivel abrir data/edges.json" << endl;
        return -1;
    }
    json jEdges;
    fEdges >> jEdges;

    int countEdges = 0;
    for (const auto& aresta : jEdges) {

        long long u = aresta.value("u", 0LL);
        long long v = aresta.value("v", 0LL);

        // verifica se tem "length" direto ou se está num sub-objeto
        double peso = 0.0;
        bool oneway = false;

        if (aresta.contains("length")) {
            peso = aresta["length"];
        } else if (aresta.contains("data") && aresta["data"].contains("length")) {
            peso = aresta["data"]["length"];
        }

        if (aresta.contains("oneway")) {
            oneway = aresta["oneway"];
        }

        // Adiciona ao grafo
        if (u != 0 && v != 0) {
            g.addAresta(u, v, peso);
            if (!oneway) {
                g.addAresta(v, u, peso); // adiciona volta se não for mão única
            }
            countEdges++;
        }
    }
    cout << "[OK] Arestas carregadas: " << countEdges << endl;
    cout << "     Total de Vertices no Grafo: " << g.verticeCount() << endl;
    fEdges.close();

    // carregar Nomes para Busca (Trie) -> label_to_nodes.json
    //mapeia "Nome da Rua" -> lista de IDs
    ifstream fLabels("data/label_to_nodes.json");
    if (!fLabels.is_open()) {
        cerr << "[ERRO] Nao foi possivel abrir data/label_to_nodes.json" << endl;
    } else {
        json jLabels;
        fLabels >> jLabels;

        int countLabels = 0;
        // itera sobre o mapa: Chave (Nome) -> valor (array de IDs)
        for (auto& element : jLabels.items()) {
            string nomeRua = element.key();
            auto ids = element.value(); // isso deve ser um array de IDs

            // pegamos o primeiro ID da lista para usar como alvo da navegação
            if (ids.is_array() && !ids.empty()) {
                long long idAlvo = ids[0];

                // insere na trie: Nome -> ID
                trie.insert(nomeRua, idAlvo);
                countLabels++;
            }
        }
        cout << "[OK] Nomes de ruas indexados na Trie: " << countLabels << endl;
        fLabels.close();
    }

    cout << "--------------------------------------------------" << endl;
    cout << "SISTEMA PRONTO PARA INICIAR." << endl;

    //inicializa a janela
    MainWindow w;

    // passa os ponteiros do Grafo e da Trie PREENCHIDOS para a janela
    w.setGrafo(&g);
    w.setTrie(&trie);

    w.show();

    return a.exec();
}
