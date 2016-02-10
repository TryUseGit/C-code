#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QIcon>
#include<QPushButton>
#include "gamewidget.h"
#include<QPalette>
#include<QPixmap>
#include<QMessageBox>
namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = 0);
    ~mainWidget();
    QPushButton* startbutton;
    QPushButton* exitbutton;
    gamewidget *gamewindow;
public slots:
    void startbutton_click();
    void exitbutton_click();

private:
    Ui::mainWidget *ui;

};

#endif // MAINWIDGET_H
