#include "maploader.h"
#include <fstream>
#include <iostream>
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

bool MapLoader::loadFiles(Grafo& g, Trie& trie) {
    cout << "--- INICIANDO CARREGAMENTO DA BASE DE DADOS (OSM) ---" << endl;

    if (!loadNodes(g, "data/nodes.json"))
        return false;

    if (!loadEdges(g, "data/edges.json"))
        return false;

    if (!loadLabels(trie, "data/label_to_nodes.json"))
        return false;

    cout << "--------------------------------------------------" << endl;
    cout << "SISTEMA PRONTO PARA INICIAR." << endl;

    return true;
}

bool MapLoader::loadNodes(Grafo& g, const string& caminho) {
    ifstream f(caminho);
    if (!f.is_open()) {
        cerr << "[ERRO] Nao foi possivel abrir " << caminho << endl;
        return false;
    }

    json j;
    f >> j;

    int count = 0;

    for (const auto& node : j) {
        if (node.contains("id") && node.contains("y") && node.contains("x")) {
            long long id = node["id"];
            double lat = node["y"];
            double lon = node["x"];

            g.setCoordenada(id, lat, lon);
            count++;
        }
    }

    cout << "[OK] Nodos carregados: " << count << endl;
    return true;
}

bool MapLoader::loadEdges(Grafo& g, const std::string& caminho){
    ifstream f(caminho);
        if (!f.is_open()) {
            cerr << "[ERRO] Nao foi possivel abrir " << caminho << endl;
            return false;
        }

        json j;
        f >> j;

        int count = 0;

        for (const auto& aresta : j) {

            long long u = aresta.value("u", 0LL);
            long long v = aresta.value("v", 0LL);

            double peso = 0.0;
            bool oneway = false;

            // verifica se tem "length" direto ou se está num sub-objeto
            if (aresta.contains("length"))
                peso = aresta["length"];
            else if (aresta.contains("data") && aresta["data"].contains("length"))
                peso = aresta["data"]["length"];

            if (aresta.contains("oneway"))
                oneway = aresta["oneway"];

            // Adiciona ao grafo
            if (u != 0 && v != 0) {
                g.addAresta(u, v, peso);
                if (!oneway)
                    g.addAresta(v, u, peso);// adiciona volta se não for mão única

                count++;
            }
        }

        cout << "[OK] Arestas carregadas: " << count << endl;
        cout << "     Total de Vertices no Grafo: "
             << g.verticeCount() << endl;

        return true;
}

bool MapLoader::loadLabels(Trie& trie, const string& caminho) {
    // carregar Nomes para Busca (Trie) -> label_to_nodes.json
    //mapeia "Nome da Rua" -> lista de IDs
    ifstream f(caminho);
    if (!f.is_open()) {
        cerr << "[ERRO] Nao foi possivel abrir " << caminho << endl;
        return false;
    }

    json j;
    f >> j;

    int count = 0;

    // itera sobre o mapa: Chave (Nome) -> valor (array de IDs)
    for (auto& element : j.items()) {
        string nomeRua = element.key();
        auto ids = element.value();


        if (ids.is_array() && !ids.empty()) {
            // pegamos o primeiro ID da lista para usar como alvo da navegação
            long long idAlvo = ids[0];

            // insere na trie
            trie.insert(nomeRua, idAlvo);
            count++;
        }
    }

    cout << "[OK] Nomes indexados na Trie: "
         << count << endl;

    return true;
}


