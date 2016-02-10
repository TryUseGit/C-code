#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("GoBang");
    this->resize(300,200);

    start = new QPushButton("Start",this);
    start->setGeometry(QRect(100,100,40,20));
    exit = new QPushButton("Exit",this);
    exit->setGeometry(QRect(150,100,40,20));

    connect(start,SIGNAL(clicked()),this,SLOT(start_click()));
    connect(exit,SIGNAL(clicked()),this,SLOT(exit_click()));
}
MainWidget::~MainWidget()
{
    delete start,exit;
    delete gw;
}
void MainWidget::start_click()
{
    gw = new Gamewidget(this);    
    gw->show();
    this->resize(600,400);
}

void MainWidget::exit_click()
{
    this->close();
}
