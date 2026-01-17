#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "grafo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Testes da classe grafo
    Grafo g(4);
    g.addAresta(0, 1, 2.5);
    g.addAresta(1, 2, 1.2);
    g.addAresta(1, 0, 2.5);
    g.addAresta(0, 2, 2.5);
    g.addAresta(0, 3, 2.5);

    qDebug() << "Vertices:" << g.verticeCount();
    qDebug() << "Vizinhos do 0:" << g.vizinhos(0).size();

    return a.exec();
}
