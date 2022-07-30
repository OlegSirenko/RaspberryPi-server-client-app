#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include "Buttons.h"

Buttons::Buttons(QWidget *parent):QWidget(parent) {
    auto *quitBtn = new QPushButton("quit", this);
    auto *openBtn = new QPushButton("Open host", this);
    connection_data = new QLabel("Push button to OPEN HOST", this);
    lbl2 = new QLabel("", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(openBtn, 2, 1);
    grid->addWidget(quitBtn, 2, 0);

    grid->addWidget(connection_data, 3, 0);
    grid->addWidget(lbl2, 4, 0);

    setLayout(grid);
    server = new QTcpServer();

    //Connect signal slot
    connect(server,&QTcpServer::newConnection,this,&Buttons::server_New_Connect);
    connect(quitBtn, &QPushButton::clicked, this, QApplication::quit);
    connect(openBtn, &QPushButton::clicked, this, &Buttons::open_host);
}

void Buttons::server_New_Connect() {
    socket = server->nextPendingConnection();
    qDebug("Just connected");
    //Connect the signal slot of the QTcpSocket to read the new data
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Buttons::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Buttons::socket_Disconnected);
    //Send key enablement
}

void Buttons::socket_Read_Data() {
    QByteArray buffer;
    //Read Buffer Data
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        connection_data -> setText(buffer);
        qDebug()<<buffer;
    }
}

void Buttons::socket_Disconnected() {
    connection_data ->setText("Disconnected");
}

void Buttons::open_host(){
    int port = 12345;
    if(!server->listen(QHostAddress::Any, port))
    {
        //If an error occurs, the error message is output
        qDebug()<<server->errorString();
        return;
    }

    qDebug("Listen succeessfully!") ;
}