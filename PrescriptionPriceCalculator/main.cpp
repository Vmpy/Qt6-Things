#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QIcon icon("./icon.png");
    w.setWindowIcon(icon);
    w.showMaximized();
    return a.exec();
}
