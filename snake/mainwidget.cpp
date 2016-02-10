#include "mainwidget.h"
mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(391,220);
    this->setWindowTitle("snack");
    QPalette  palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":new/prefix1/img/back_color.jpg").scaled(this->size())));
//    palette.setBrush(QPalette::Background,QBrush(Qt::black));
    this->setPalette(palette);
    startbutton = new QPushButton("start",this);
    startbutton->setIconSize(QSize(50,20));
    startbutton->setGeometry(QRect(320,50,50,20));
    startbutton->setFlat(true);
    QObject::connect(startbutton,SIGNAL(clicked()),this,SLOT(startbutton_click()));
    exitbutton = new QPushButton("exit",this);
    exitbutton->setIconSize(QSize(50,20));
    exitbutton->setGeometry(QRect(320,70,50,20));
    exitbutton->setFlat(true);
    this->connect(exitbutton,SIGNAL(clicked()),this,SLOT(exitbutton_click()));
}
mainWidget::~mainWidget()
{
    delete startbutton;
    delete exitbutton;
    delete gamewindow;
}
void mainWidget::startbutton_click(){
    gamewindow = new gamewidget(this);
    this->hide();
    gamewindow->show();
}
void mainWidget::exitbutton_click(){
    int rep = QMessageBox::question(this,"warnning","Are you sure to exit",QMessageBox::StandardButton::Yes,QMessageBox::StandardButton::No);
    if(rep==QMessageBox::Yes){
        this->close();
   }
}
