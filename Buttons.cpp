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
    address = new QLineEdit(this);
    auto *grid = new QGridLayout(this);
    grid->addWidget(openBtn, 2, 1);
    grid->addWidget(quitBtn, 2, 0);
    grid->addWidget(sendBtn, 2,2);
    grid->addWidget(address, 3, 1);
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
    connection_data ->setText("Someone just connected");
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
        client_message -> setText(buffer);
        qDebug()<<buffer;
    }
}

void Buttons::socket_Disconnected() {
    connection_data ->setText("Disconnected");
    client_message->setText("");
}

void Buttons::open_host(){
    QString addr;

    qDebug() << address->text();

    addr = address->text();

    if(!server->listen(QHostAddress(addr), 5500)) {
        //If an error occurs, the error message is output
        qDebug()<<server->errorString();
        return;
    }
    QString str;
    str= "Host opened with port 5500 and ip address " + addr;
    connection_data ->setText(str);
    qDebug("Listen succeessfully!") ;
}

void Buttons::send_to_client() {
    socket->write("Hello there!");
    socket->flush();
}

