#ifndef GRAFO_H
#define GRAFO_H
#include <vector>

using namespace std;

// Estrutura da aresta do grafo, armazena destino e peso
struct Aresta {
    long dest;
    double peso;
};

class Grafo
{
public:
    Grafo(int vertices);

    // Função para adicinoar aresta ponderada entre dois vertices
    void addAresta(long vertice, long dest, double peso);

    // Vetor que vai armazenar todos vizinhos de um determinado vértice
    const vector<Aresta>& vizinhos(int nVertices) const;

    // Retorna a quantidade de vértices do grafo
    int verticeCount() const;
private:
    // Lista de adjacencia que vai representar o grafo
    vector<vector<Aresta> > adjLista;
};

#endif // GRAFO_H
