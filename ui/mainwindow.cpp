    #include "mainwindow.h"
    #include "ui_mainwindow.h"
    #include <QMessageBox>
    #include <QQmlContext>
    #include <QQuickItem>
    #include <QVariant>
    #include <QGeoCoordinate>
    #include <QDebug>

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , grafo(nullptr)
        , trie(nullptr)
    {
        ui->setupUi(this);

        // 1. configurar o mapa (QQuickWidget)
        mapWidget = new QQuickWidget(this);
        mapWidget->setSource(QUrl(QStringLiteral("qrc:/mapa.qml"))); // Ou caminho absoluto para teste
        mapWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

        // adiciona o mapa ao layout
        ui->mapContainer->addWidget(mapWidget);

        // 2. Inicializar Models de Autocomplete
        modelOrigem = new QStringListModel(this);
        modelDestino = new QStringListModel(this);

        configurarCompleter(ui->inputOrigem, completerOrigem, modelOrigem, SLOT(atualizarSugestoesOrigem(QString)));
        configurarCompleter(ui->inputDestino, completerDestino, modelDestino, SLOT(atualizarSugestoesDestino(QString)));
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::setGrafo(Grafo *g) { this->grafo = g; }
    void MainWindow::setTrie(Trie *t) { this->trie = t; }

    void MainWindow::configurarCompleter(QLineEdit* editor, QCompleter*& completer, QStringListModel*& model, const char* slot) {
        completer = new QCompleter(model, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
        editor->setCompleter(completer);

        // conecta a digitação pra busca na Trie
        connect(editor, SIGNAL(textEdited(QString)), this, slot);
    }

    // slot: busca na Trie enquanto digita (Origem)
    void MainWindow::atualizarSugestoesOrigem(const QString &texto) {

        qDebug() << "Digitando Origem: " << texto;

        if (!trie) {
            qDebug() << "ERRO: Trie é nula!";
            return;
        }

        // busca na Trie
        vector<string> sugs = trie->autocomplete(texto.toStdString());

        qDebug() << "Sugestões encontradas: " << sugs.size();

        QStringList qSugs;
        for(const auto& s : sugs) {
            qSugs << QString::fromStdString(s);
        }

        // atualiza o autocomplete
        modelOrigem->setStringList(qSugs);

        // força o popup a aparecer se tiver dados
        if (!qSugs.isEmpty()) {
            completerOrigem->complete();
        }
    }

    // busca na Trie enquanto digita destino
    void MainWindow::atualizarSugestoesDestino(const QString &texto) {
        if (!trie || texto.length() < 3) return;

        vector<string> sugs = trie->autocomplete(texto.toStdString());
        QStringList qSugs;
        for(const auto& s : sugs) qSugs << QString::fromStdString(s);

        modelDestino->setStringList(qSugs);
    }

    // botão de rota
    void MainWindow::on_btnCalcular_clicked() {
        if (!grafo || !trie) return;

        QString txtOrigem = ui->inputOrigem->text();
        QString txtDestino = ui->inputDestino->text();

        // busca IDs na Trie
        long long idOrigem = trie->buscarId(txtOrigem.toStdString());
        long long idDestino = trie->buscarId(txtDestino.toStdString());

        if (idOrigem == -1 || idDestino == -1) {
            QMessageBox::warning(this, "Erro", "Local não encontrado na base de dados.");
            return;
        }

        // executa Dijkstra
        list<long long> caminhoIds = grafo->dijkstra(idOrigem, idDestino);

        if (caminhoIds.empty()) {
            QMessageBox::information(this, "Aviso", "Não há rota entre estes pontos.");
            return;
        }

        //converte IDs para coordenadas
        QVariantList caminhoCoords;

        for (long long id : caminhoIds) {
            double lat = grafo->getLatitude(id);
            double lon = grafo->getLongitude(id);

            caminhoCoords.append(QVariant::fromValue(QGeoCoordinate(lat, lon)));
        }

        // envia para o QML desenhar
        QObject* rootObject = mapWidget->rootObject();
        QMetaObject::invokeMethod(rootObject, "desenharRota",
                                  Q_ARG(QVariant, QVariant::fromValue(caminhoCoords)));
    }
