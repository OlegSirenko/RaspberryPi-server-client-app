#include "Connection.h"
#include "Buttons.h"

Connection::Connection(QObject *parent):QObject(parent) {
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()),this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 5555))
    {
        qDebug() << "Server could not start";
        Buttons buttons;
        buttons.lbl2->setText("Server could not start");
    }
    else
    {
        qDebug() << "Server started!";
        Buttons buttons;
        buttons.lbl2->setText("Server started");
    }
}

void Connection::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    qDebug() << "Connected";
    socket->flush();
    Buttons buttons;
    buttons.lbl2->setText("Connected");
    socket->waitForBytesWritten(1000);
    socket->close();
}
