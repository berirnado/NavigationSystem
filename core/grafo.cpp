#include "grafo.h"

using namespace std;

Grafo::Grafo(int vertices) : adjLista(vertices) {}

void Grafo::addAresta(long origem, long destino, double peso) {
    //Adiciona aresta no vértice passado como origem
    adjLista[origem].push_back({destino, peso});
}

const vector<Aresta>& Grafo::vizinhos(int nVertices) const {
    return adjLista[nVertices];
}

int Grafo::verticeCount() const {
    return adjLista.size();
}
