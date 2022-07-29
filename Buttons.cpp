#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include "Buttons.h"

Buttons::Buttons(QWidget *parent):QWidget(parent) {
    auto *quitBtn = new QPushButton("quit", this);
    lbl = new QLabel("status = 0", this);
    lbl2 = new QLabel("Not Connected", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(quitBtn, 2, 0);

    grid->addWidget(lbl, 3, 0);
    grid->addWidget(lbl2, 4, 0);

    setLayout(grid);
    server = new QTcpServer();

    //Connect signal slot
    connect(server,&QTcpServer::newConnection,this,&Buttons::server_New_Connect);
    connect(quitBtn, &QPushButton::clicked, this, &Buttons::OnQuit);
}


void Buttons::OnQuit() {
    lbl->setText("Quited");
    QApplication::quit();
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
        lbl2 ->setText(buffer);
        //Refresh display
    }
}

void Buttons::socket_Disconnected() {
    lbl2 ->setText("Disconnected");
    qDebug("Disconnected");
}