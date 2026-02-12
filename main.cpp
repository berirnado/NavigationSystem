#include <QApplication>
#include <QDebug>
#include "grafo.h"
#include "trie.h"
#include "dijkstra.h"
#include "mainwindow.h"
#include "maploader.h"

#include "nlohmann/json.hpp" // Certifique-se que essa lib está inclusa
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Inicializa as estruturas principais
    Grafo g;
    Trie trie;

    MapLoader loader;

    // carrega os arquivos da pasta data
    if (!loader.loadFiles(g, trie)) {
        cerr << "Falha no carregamento dos dados." << endl;
        return -1;
    }

    //inicializa a janela
    MainWindow w;

    //Inicializa Dijkstra
    Dijkstra dijkstra = Dijkstra(g);

    // passa os ponteiros do Grafo e da Trie PREENCHIDOS para a janela
    w.setGrafo(&g);
    w.setTrie(&trie);
    w.setDijkstra(&dijkstra);

    w.show();

    return a.exec();
}
