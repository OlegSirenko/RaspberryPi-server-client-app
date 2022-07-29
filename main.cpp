#include <QApplication>
#include "Buttons.h"
#include "Connection.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Buttons window;
    window.setWindowTitle("Host");
    window.show();
    return QApplication::exec();
}