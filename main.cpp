#include "mainwindow.h"
#include "app/app.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App app;
    return a.exec();
}
