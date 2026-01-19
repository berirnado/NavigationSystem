#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include "grafo.h"

using namespace std;

class MapLoader
{
    //armazena o caminho pro diretório dos jsons a serem lidos
    string dirPath;
public:
    MapLoader(string dirPath);

    // Le o arquivo edges.json e transforma no grafo
    void loadEdges(Grafo& grafo);
};

#endif // MAPLOADER_H
