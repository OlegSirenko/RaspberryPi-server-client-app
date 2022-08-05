//
// Created by tehnokrat on 26.07.22.
//

#ifndef RASPBERRYPI_PROJECT_BUTTONS_H
#define RASPBERRYPI_PROJECT_BUTTONS_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QTcpServer>
#include <QTcpSocket>


class Buttons : public QWidget {
public:
    Buttons(QWidget *parent = nullptr);
private slots:
    void server_New_Connect();
    void socket_Read_Data();
    void socket_Disconnected();
    void open_host();
    void close_host();
    void send_to_client();
private:
    QPushButton *quitBtn;
    QPushButton *openBtn;
    QPushButton *sendBtn;
    QLabel *connection_data;
    QLabel *client_message;
    QLabel *descLne;
    QLineEdit *address;
    QLineEdit *port;
    QLineEdit *messageToClient;
    QTcpServer* server;
    QTcpSocket* socket{};
};

#endif //RASPBERRYPI_PROJECT_BUTTONS_H
