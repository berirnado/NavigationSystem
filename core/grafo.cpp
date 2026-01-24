#include "grafo.h"
#include <limits>
#include <algorithm> // ai usa reverse() no final do Dijkstra

using namespace std;

// construtor - inicializa o contador de vértices
Grafo::Grafo() {
    numVertices = 0;
}

// converte um ID gigante do OSM para id interno do array da lista de adj
// se o ID é novo, ele cria o cadastro automaticamente.
int Grafo::obterIndice(long long idOsm) {
    // verifica se o id para esse osm ja existe
    if (idMap.find(idOsm) != idMap.end()) {
        return idMap[idOsm]; // retorna o índice já existente
    }

    //  se é novo, cria um novo índice sequencial
    int novoIndice = numVertices;
    numVertices++;

    // salva no mapa
    idMap[idOsm] = novoIndice;

    // salva no mapa reverso
    // Dijkstra retorna os IDs reais no final
    indiceParaIdMap[novoIndice] = idOsm;

    // expande o vetor de adjacência para caber o novo vértice
    adjLista.resize(numVertices);

    return novoIndice;
}

void Grafo::addAresta(long long idOrigem, long long idDestino, double peso) {
    // primeiro, descobre ou cria os índices internos
    int iOrigem = obterIndice(idOrigem);
    int iDestino = obterIndice(idDestino);

    // adiciona a aresta usando os índices internos
    adjLista[iOrigem].push_back({iDestino, peso});
}

const vector<Aresta>& Grafo::vizinhos(int indiceInterno) const {
    return adjLista[indiceInterno];
}

int Grafo::verticeCount() const {
    return numVertices;
}

