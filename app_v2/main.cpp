#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QTcpServer>
#include <QTcpSocket>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();

    void server_New_Connect();

    void socket_Read_Data();

    void socket_Disconnected();

private:
    QTcpServer* server;
    QTcpSocket* socket{};
};


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    server = new QTcpServer();

    //Connect signal slot
    connect(server,&QTcpServer::newConnection,this,&MainWindow::server_New_Connect);
}

MainWindow::~MainWindow()
{
    server->close();
    server->deleteLater();
}

void MainWindow::on_pushButton_Listen_clicked()
{
    if(pushButton_Listen->text() == tr("Interception"))
    {
        //Get the port number from the input box
        int port = ui->lineEdit_Port->text().toInt();

        //Listen on the specified port
        if(!server->listen(QHostAddress::Any, port))
        {
            //If an error occurs, the error message is output
            qDebug()<<server->errorString();
            return;
        }
        //Modify keyword text
        ui->pushButton_Listen->setText("Cancel interception");
        qDebug()<< "Listen succeessfully!";
    }
    else
    {
        //If you are connecting
        if(socket->state() == QAbstractSocket::ConnectedState)
        {
            //Close connection
            socket->disconnectFromHost();
        }
        //Cancel interception
        server->close();
        //Modify keyword text
        ui->pushButton_Listen->setText("Interception");
        //Send button failure
        ui->pushButton_Send->setEnabled(false);
    }

}

void MainWindow::on_pushButton_Send_clicked()
{
    qDebug() << "Send: " << ui->textEdit_Send->toPlainText();
    //Get the content of the text box and send it as ASCII code
    socket->write(ui->textEdit_Send->toPlainText().toLatin1());
    socket->flush();
}

void MainWindow::server_New_Connect()
{
    //Getting Client Connection
    socket = server->nextPendingConnection();
    //Connect the signal slot of the QTcpSocket to read the new data
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);
    //Send key enablement
    ui->pushButton_Send->setEnabled(true);

    qDebug() << "A Client connect!";
}

void MainWindow::socket_Read_Data()
{
    QByteArray buffer;
    //Read Buffer Data
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = ui->textEdit_Recv->toPlainText();
        str+=tr(buffer);
        //Refresh display
    }
}

void MainWindow::socket_Disconnected()
{
    //Send button failure
    ui->pushButton_Send->setEnabled(false);
    qDebug() << "Disconnected!";
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    window.resize(250, 500);
    window.setWindowTitle("Host");
    window.show();
    return QApplication::exec();
}