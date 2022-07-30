#include <QApplication>
#include "Buttons.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Buttons window;
    window.resize(560, 800);
    window.setWindowTitle("Host");
    window.show();
    return QApplication::exec();
}