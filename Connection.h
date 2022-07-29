#ifndef RASPBERRYPI_PROJECT_CONNECTION_H
#define RASPBERRYPI_PROJECT_CONNECTION_H
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class Connection : public QObject {
Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

public slots:
    void newConnection();

private:
    QTcpServer *server{};
};


#endif
