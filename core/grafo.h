#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <unordered_map> // mapear os IDs
#include <list>          // retorna o caminho do Dijkstra

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

    // adiciona aresta recebendo os IDs originais do OSM (long long)
    // o método vai converter internamente para índices 0, 1, 2...
    void addAresta(long long idOrigem, long long idDestino, double peso);

    // retorna vizinhos baseado no índice interno
    const vector<Aresta>& vizinhos(int indiceInterno) const;

    // retorna quantidade total de vértices
    int verticeCount() const;

    // protótipo do algoritmo de Dijkstra
    // retorna uma lista com os IDs do caminho encontrado
    list<long long> dijkstra(long long idOrigem, long long idDestino);

private:
    // lista de adjacência (o índice do vetor é o índice interno do vértice)
    vector<vector<Aresta>> adjLista;

    // tabela de Tradução: ID OSM (long long) -> Índice Interno (int)
    unordered_map<long long, int> idMap;

    // tabela Inversa (opcional, mas útil para o Dijkstra retornar os IDs originais no final)
    unordered_map<int, long long> indiceParaIdMap;

    int numVertices;

    // método auxiliar privado: Converte ID OSM -> Índice Interno
    // se o ID não existir, ele cria um novo índice automaticamente
    int obterIndice(long long idOsm);
};

#endif // GRAFO_H
