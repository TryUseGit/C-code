#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QRect>
#include "gamewidget.h"
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    QPushButton* start;
    QPushButton* exit;
public slots:
    void start_click();
    void exit_click();
private:
    Gamewidget* gw;
};

#endif // MAINWIDGET_H
