#include <QWidget>
#include <QApplication>
#include "Buttons.h"

Buttons::Buttons(QWidget *parent):QWidget(parent) {
    QWidget::setGeometry(1380, 200, 100, 300);
    quitBtn = new QPushButton("quit", this);
    openBtn = new QPushButton("Open host", this);
    sendBtn = new QPushButton("Send hello message", this);

    connection_data = new QLabel("Push button to OPEN HOST", this);
    client_message = new QLabel("", this);
    descLne = new QLabel("Put address and port");

    address = new QLineEdit("127.0.0.1",this);
    port = new QLineEdit("5500", this);
    messageToClient = new QLineEdit("Message to client", this);
    auto *grid = new QGridLayout(this);

    grid->addWidget(quitBtn, 0, 0);
    grid->addWidget(openBtn, 0, 1);
    grid->addWidget(sendBtn, 0,2);

    grid->addWidget(connection_data, 2, 0);     // |    connection data    | client message | message send |
    grid->addWidget(client_message, 2, 1);      // |    quit               | open host      | send message |
    grid->addWidget(messageToClient, 2, 2);     // |Write down addr & port |     address    | port         |

    grid->addWidget(descLne, 3, 0);
    grid->addWidget(address, 3, 1);
    grid->addWidget(port, 3, 2);

    setLayout(grid);
    server = new QTcpServer();

    sendBtn->setEnabled(false);

    //Connect signal slot
    connect(server,&QTcpServer::newConnection,this,&Buttons::server_New_Connect);
    connect(quitBtn, &QPushButton::clicked, this, QApplication::quit);
    connect(openBtn, &QPushButton::clicked, this, &Buttons::open_host);
    connect(sendBtn, &QPushButton::clicked, this, &Buttons::send_to_client);
}

void Buttons::server_New_Connect() {
    socket = server->nextPendingConnection();
    connection_data ->setText("Someone just connected");
    //Connect the signal slot of the QTcpSocket to read the new data
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Buttons::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Buttons::socket_Disconnected);
    sendBtn->setEnabled(true);
}

void Buttons::socket_Read_Data() {
    QByteArray buffer;
    buffer = socket->readAll(); //Read Buffer Data
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
    QString p;

    addr = address->text();
    p = port->text();
    if(openBtn->text() == "Open host") {
        if(!server->listen(QHostAddress(addr), p.toInt())) {
            //If an error occurs, the error message is output
            qDebug()<<server->errorString();
            connection_data ->setText("ERROR: " + server->errorString());
            return;
        }
        QString str;
        str= "Host opened with port \n" + p +" \nand ip address \n" + addr;
        connection_data ->setText(str);
        openBtn->setText("Close host");
        qDebug("Listen start");
    }
    else {
        server->close();
        openBtn->setText("Open host");
        connection_data->setText("Host closed");
        client_message->setText("");
    }

}

void Buttons::send_to_client() {
    QString data;
    data = messageToClient->text();
    socket->write(data.toUtf8());
    socket->flush();
    socket->close();
}



