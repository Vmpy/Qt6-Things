#include "mainwindow.h"

#include <QApplication>
#include <Qfile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile qss(":/style/style.qss");
    if(qss.open(QFile::ReadOnly))
    {
        //qDebug("open qss success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
    }
    qss.close();

    w.setWindowTitle("相册浏览器");
    w.showMaximized();
    return a.exec();
}
