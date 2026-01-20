#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

// estrutura da aresta
struct Aresta {
    int dest;
    double peso;
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

    // retorna uma lista com os ids do caminho encontrado
    list<long long> dijkstra(long long idOrigem, long long idDestino);

private:
    // lista de adjacência
    vector<vector<Aresta>> adjLista;

    // tabela que relaciona os ids osmid para os ids do array
    unordered_map<long long, int> idMap;

    // tabela Inversa
    unordered_map<int, long long> indiceParaIdMap;

    int numVertices;

    // retorna o id interno referente ao osmid e se nao existir cria
    int obterIndice(long long idOsm);
};

#endif // GRAFO_H
