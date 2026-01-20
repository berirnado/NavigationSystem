#include "grafo.h"
#include <limits>
#include <algorithm> // ai usa reverse() no final do Dijkstra

using namespace std;

<<<<<<< HEAD
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
=======
// construtor - inicializa o contador de vértices
Grafo::Grafo() {
    numVertices = 0;
>>>>>>> 5be1326486e8f5d72002d6da933c7bd32cbde874
}

// converte um ID gigante do OSM
// se o ID é novo, ele cria o cadastro automaticamente.
int Grafo::obterIndice(long long idOsm) {
    // 1. Verifica se já conhecemos esse ID
    if (idMap.find(idOsm) != idMap.end()) {
        return idMap[idOsm]; // retorna o índice já existente
    }

    //  se é novo, cria um novo índice sequencial
    int novoIndice = numVertices;
    numVertices++;

    // salva no mapa (Id OSM -> Índice Interno)
    idMap[idOsm] = novoIndice;

    // salva no mapa reverso (Índice Interno -> Id OSM)
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
    // o vetor agora está seguro e não vai estourar a memória
    adjLista[iOrigem].push_back({iDestino, peso});
}

const vector<Aresta>& Grafo::vizinhos(int indiceInterno) const {
    return adjLista[indiceInterno];
}

int Grafo::verticeCount() const {
    return numVertices;
}

// implementação do Dijkstra
// falta completar --- ARRUMAR
list<long long> Grafo::dijkstra(long long idOrigem, long long idDestino) {
    list<long long> caminho;

    // verificação de segurança
    if (idMap.find(idOrigem) == idMap.end() || idMap.find(idDestino) == idMap.end()) {
        return caminho; // retorna vazio se origem ou destino não existem
    }

    int iOrigem = idMap[idOrigem];
    int iDestino = idMap[idDestino];

    // TO-DO: FALTA a lógica da priority_queue aqui

    return caminho;
}
