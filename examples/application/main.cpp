#include <QApplication>

#include "QRootWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRootWidget r;
    r.resize(800,600);
    r.show();
    return a.exec();
}

