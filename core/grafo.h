#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <unordered_map>

using namespace std;

// Estrutura da aresta do grafo, armazena destino e peso
struct Aresta {
    long dest;
    double peso;
};

class Grafo
{
public:
    Grafo();

    // Função para adicinoar aresta ponderada entre dois vertices
    void addAresta(long vertice, long dest, double peso, bool isOneWay);

    // Vetor que vai armazenar todos vizinhos de um determinado vértice
    const vector<Aresta>& vizinhos(int nVertices) const;

    // Retorna a quantidade de vértices do grafo
    int verticeCount() const;
private:
    // Lista de adjacencia que vai representar o grafo
    vector<vector<Aresta> > adjLista;

    // Hash que vai converter os valores osmid para caber no array do grafo
    unordered_map<long, long> osmidParaIndice;

    // Cria caso ainad nao exista ou retorna indice referente ao numero osmid do vértice
    long addVertice(long osmid);
};

#endif // GRAFO_H
