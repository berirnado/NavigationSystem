#include "grafo.h"
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

// construtor - inicializa o contador de vértices
Grafo::Grafo() {
    numVertices = 0;
}

// converte um ID gigante do OSM para id interno do array da lista de adj
// se o ID é novo, ele cria o cadastro automaticamente
int Grafo::obterIndice(long long idOsm) {
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

// latitude e longitude do mapa

void Grafo::setCoordenada(long long id, double lat, double lon) {
    coordenadas[id] = {lat, lon};
}

double Grafo::getLatitude(long long id) {
    if (coordenadas.find(id) != coordenadas.end()) {
        return coordenadas[id].lat;
    }
    return 0.0; // 0 se nao encontrar
}

double Grafo::getLongitude(long long id) {
    if (coordenadas.find(id) != coordenadas.end()) {
        return coordenadas[id].lon;
    }
    return 0.0;
}

std::unordered_map<long long, int>& Grafo::getIdMap() {
    return idMap;
}

std::unordered_map<int, long long>& Grafo::getReverseIdMap() {
    return indiceParaIdMap;
}
