#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <limits>
#include <functional>
#include "grafo.h"

class Dijkstra {
public:
    Dijkstra(Grafo& grafo);

    std::list<long long> executar(long long idOrigem, long long idDestino);

private:
    Grafo& grafo;
};

#endif
