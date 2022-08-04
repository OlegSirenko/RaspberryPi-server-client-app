#include <QApplication>
#include "Buttons.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Buttons window;
    window.resize(200, 300);
    window.setWindowTitle("Host");
    window.show();
    return QApplication::exec();
}