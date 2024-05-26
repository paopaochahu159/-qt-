#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(460,290);
    w.setWindowTitle("今天的实时天气信息");
    w.show();
    return a.exec();
}
