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

// DIJKSTRA

list<long long> Grafo::dijkstra(long long idOrigem, long long idDestino) {
    list<long long> caminho;

    // verifica se origem e destino existem no grafo
    if (idMap.find(idOrigem) == idMap.end() || idMap.find(idDestino) == idMap.end()) {
        return caminho; // Retorna vazio se não existirem
    }

    int startIdx = idMap[idOrigem];
    int endIdx = idMap[idDestino];
    int n = numVertices;

    const double INF = numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> parent(n, -1);

    // priority Queue (Min-Heap): armazena {distancia, vertice}
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    dist[startIdx] = 0;
    pq.push({0, startIdx});

    while (!pq.empty()) {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;
        if (u == endIdx) break; //

        for (const auto& aresta : adjLista[u]) {
            int v = aresta.dest;
            double peso = aresta.peso;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // reconstrução do caminho
    if (parent[endIdx] == -1 && startIdx != endIdx) {
        return caminho; // não tem caminho
    }

    int curr = endIdx;
    while (curr != -1) {
        caminho.push_front(indiceParaIdMap[curr]);
        if (curr == startIdx) break;
        curr = parent[curr];
    }

    return caminho;
}
