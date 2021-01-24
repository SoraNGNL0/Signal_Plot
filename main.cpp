#include "mainwindow.h"
#include <QApplication>

bool ADRun;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ADRun = false;
    MainWindow w;
    w.show();

    return a.exec();
}
