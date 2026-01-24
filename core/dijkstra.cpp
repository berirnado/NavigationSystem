#include "dijkstra.h"


Dijkstra::Dijkstra()
{

}

// implementação do Dijkstra
list<long long> Dijkstra::executar(long long idOrigem, long long idDestino, Grafo& grafo) {
    list<long long> caminho;

    // verificação de segurança
    if (idMap.find(idOrigem) == idMap.end() || idMap.find(idDestino) == idMap.end()) {
        return caminho; // retorna vazio se origem ou destino não existem
    }

    int origem = idMap[idOrigem];
    int destino = idMap[idDestino];

    int V = grafo.verticeCount();

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    const double infinito = numeric_limits<double>::infinity();

    // inicializa vetor de dist com infinito pra comparação sempre substituir pelo caminho encontrado
    vector<double> dist(V, infinito);

    // vetor que vai ser utilizado pra reconstrução do caminho pois djikstra em si só retorna a distancia mínima
    vector<int> anterior(V, -1);

    dist[origem] = 0;
    pq.emplace(0, origem);

    while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // ignora entrada velha
            if (d > dist[u]){
                continue;
            }

            // se chegou no destino, pode parar
            if (u == destino){
                break;
            }

            // relaxamento das arestas
            for (const Aresta& a : grafo.vizinhos(u)) {
                int v = a.dest;
                double peso = a.peso;

                // caso a distancia que temos armazanada no array dist for maior do que o caminho encontrado a partir do vértice atual para o vértice v
                if (dist[v] > dist[u] + peso) {
                    // vamos atualizar a distancia para o vértice v pois achamos uma distancia menor
                    dist[v] = dist[u] + peso;
                    // array de anterior vai ser util pra reconstruir o caminho no final
                    anterior[v] = u;
                    // adicionamos a nova distancia encontrada e o vértice na pq
                    pq.push({dist[v], v});
                }
            }
        }

        // se não existe caminho
        if (anterior[destino] == -1)
            return caminho;

        // Reconstrução do caminho (retorna em osmid)
        for (int v = destino; v != -1; v = anterior[v]) {
            caminho.push_front(reverseIdMap[v]);
        }

    return caminho;
}
