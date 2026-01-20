#include "dijkstra.h"


Dijkstra::Dijkstra()
{

}

// implementação do Dijkstra
// falta completar
list<long long> Djikstra::executar(long long idOrigem, long long idDestino) {
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
