//
// Created by tehnokrat on 26.07.22.
//

#ifndef RASPBERRYPI_PROJECT_BUTTONS_H
#define RASPBERRYPI_PROJECT_BUTTONS_H
#include "QWidget"
#include <QLabel>
#include <QGridLayout>
#include <QTcpServer>
#include <QTcpSocket>


class Buttons : public QWidget {
public:
    Buttons(QWidget *parent = nullptr);
private slots:
    void OnQuit();
    void server_New_Connect();
    void socket_Read_Data();
    void socket_Disconnected();
    void open_host();

private:
    QLabel *connection_data;
    QLabel *lbl2;
    QTcpServer* server;
    QTcpSocket* socket{};
};

#endif //RASPBERRYPI_PROJECT_BUTTONS_H
