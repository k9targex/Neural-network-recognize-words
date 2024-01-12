#include "mainwindow.h"
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile ss(":/new/prefix1/style.css");
    ss.open(QFile::ReadOnly);

    a.setStyleSheet(ss.readAll());
    MainWindow w;
    w.setObjectName("Main");
    w.show();
    return a.exec();
}
