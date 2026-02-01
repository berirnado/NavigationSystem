#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCompleter>
#include <QStringListModel>
#include <QQuickWidget>
#include <QLineEdit>
#include "../core/grafo.h"
#include "../core/trie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // métodos para injetar as dependências
    void setGrafo(Grafo* g);
    void setTrie(Trie* t);

private slots:
    void on_btnCalcular_clicked(); // Botão da interface
    void atualizarSugestoesOrigem(const QString &texto);
    void atualizarSugestoesDestino(const QString &texto);

private:
    Ui::MainWindow *ui;

    // ponteiros pra logica
    Grafo* grafo;
    Trie* trie;

    // automcomplete
    QCompleter *completerOrigem;
    QCompleter *completerDestino;
    QStringListModel *modelOrigem;
    QStringListModel *modelDestino;

    // mapa
    QQuickWidget *mapWidget;

    // helper para buscar sugestões
    void configurarCompleter(QLineEdit* editor, QCompleter*& completer, QStringListModel*& model, const char* slot);
};
#endif // MAINWINDOW_H
