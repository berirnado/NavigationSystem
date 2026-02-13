#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include "grafo.h"
#include "trie.h"


using namespace std;

class MapLoader
{
public:
    bool loadFiles(Grafo& g, Trie& t);

private:
    // Carrega as arestas do grafo
    bool loadEdges(Grafo& grafo, const std::string& caminho);
    // Carrega os nós do grafo
    bool loadNodes(Grafo& grafo, const std::string& caminho);
    // Carrega as Labels do arquivo de labels
    bool loadLabels(Trie& trie, const std::string& caminho);
}
;

#endif // MAPLOADER_H
