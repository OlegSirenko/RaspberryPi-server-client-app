#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include "Buttons.h"

Buttons::Buttons(QWidget *parent):QWidget(parent) {
    auto *quitBtn = new QPushButton("quit", this);
    auto *openBtn = new QPushButton("Open host", this);
    auto* sendBtn = new QPushButton("Send hello message", this);
    connection_data = new QLabel("Push button to OPEN HOST", this);
    client_message = new QLabel("", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(openBtn, 2, 1);
    grid->addWidget(quitBtn, 2, 0);
    grid->addWidget(sendBtn, 2,2);

    grid->addWidget(connection_data, 3, 0);
    grid->addWidget(client_message, 4, 0);

    setLayout(grid);
    server = new QTcpServer();

    //Connect signal slot
    connect(server,&QTcpServer::newConnection,this,&Buttons::server_New_Connect);
    connect(quitBtn, &QPushButton::clicked, this, QApplication::quit);
    connect(openBtn, &QPushButton::clicked, this, &Buttons::open_host);
    connect(sendBtn, &QPushButton::clicked, this, &Buttons::send_to_client);
}

void Buttons::server_New_Connect() {
    socket = server->nextPendingConnection();
    qDebug("Just connected");
    //Connect the signal slot of the QTcpSocket to read the new data
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Buttons::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Buttons::socket_Disconnected);
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
    client_message->setText("");
}

void Buttons::open_host(){
    QString address;
    int port = 12345;
    address = "127.0.0.1";
    if(!server->listen(QHostAddress(address), port)) {
        //If an error occurs, the error message is output
        qDebug()<<server->errorString();
        return;
    }
    QString str;
    str= "Host opened with port 12345 and ip address" + address;
    connection_data ->setText(str);
    qDebug("Listen succeessfully!") ;
}

void Buttons::send_to_client() {
    socket->write("Hello there!");
    socket->flush();
}

