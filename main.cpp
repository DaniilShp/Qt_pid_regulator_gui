#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QPushButton, QLabel { background-color: #414141; color: #ffffff; }");
    MainWindow w;
     w.setFixedSize(1280, 720);
    w.show();
    return a.exec();
}
