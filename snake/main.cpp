#include "mainwidget.h"
#include <QApplication>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget w;
    w.show();
    w.startbutton;
    return a.exec();
}
