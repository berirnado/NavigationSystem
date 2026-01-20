#include "grafo.h"

using namespace std;

Grafo::Grafo() = default;

long Grafo::addVertice(long indice_osmid){
    auto hashItem = osmidParaIndice.find(indice_osmid);
    if(hashItem != osmidParaIndice.end()){
        //já existe o vértice, retornar seu indice do array
        return hashItem->second;
    }

    // não existe o vértice, adicionar na hash
    long novoIndice = adjLista.size();
    osmidParaIndice[indice_osmid] = novoIndice;

    // abre espaço na lista de adjacencia
    adjLista.push_back({});

    return novoIndice;
}

void Grafo::addAresta(long origem_osmid, long destino_osmid, double peso, bool isOneWay) {
    // Cria vértice referente ou busca ja existente retornando o indice ideal pra colocar no array
    long origem = addVertice(origem_osmid);
    long destino = addVertice(destino_osmid);

    //Adiciona aresta no vértice passado como origem
    adjLista[origem].push_back({destino, peso});

    // caso seja mao dupla vai adicionar a aresta bidirecional
    if(!isOneWay){
        adjLista[destino].push_back({origem, peso});
    }
}

const vector<Aresta>& Grafo::vizinhos(int nVertices) const {
    return adjLista[nVertices];
}

int Grafo::verticeCount() const {
    return adjLista.size();
}
