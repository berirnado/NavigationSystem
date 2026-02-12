#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

// aresta
struct Aresta {
    int dest;
    double peso;
};

// guarda latitude e longitudea
struct Coordenada {
    double lat;
    double lon;
};

class Grafo
{
public:
    // sem tamanho fixo
    Grafo();

    // adiciona aresta recebendo os IDs originais do OSM
    void addAresta(long long idOrigem, long long idDestino, double peso);

    // retorna vizinhos baseado no índice interno
    const vector<Aresta>& vizinhos(int indiceInterno) const;

    // retorna quantidade total de vértices
    int verticeCount() const;

    // retorna uma lista com os ids do caminho encontrado (Dijkstra)
    list<long long> dijkstra(long long idOrigem, long long idDestino);


    // define a coordenada de um nó
    void setCoordenada(long long id, double lat, double lon);

    // retorna a latitude de um ID original
    double getLatitude(long long id);

    // retorna a longitude de um ID original
    double getLongitude(long long id);

    // retorna o idMap (usado em dijkstra)
    std::unordered_map<long long, int>& getIdMap();

    // retorna o reverseIdMap (usado em dijkstra)
    std::unordered_map<int, long long>& getReverseIdMap();

private:
    // lista de adjacencia
    vector<vector<Aresta>> adjLista;

    // tabela que relaciona os ids osmid para os ids do array
    unordered_map<long long, int> idMap;

    // tabela inversa
    unordered_map<int, long long> indiceParaIdMap;

    // tabela de coordenadas
    unordered_map<long long, Coordenada> coordenadas;

    int numVertices;

    // retorna o id interno referente ao osmid e se nao existir cria
    int obterIndice(long long idOsm);
};

#endif // GRAFO_H
