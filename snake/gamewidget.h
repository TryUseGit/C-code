#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QDialog>
#include<QPushButton>
#include<QPainter>
#include<QTime>
#include<QTimer>
#include<QMessageBox>
#include <QSound>
#include<QKeyEvent>
namespace Ui {
class gamewidget;
}

class gamewidget : public QDialog
{
    Q_OBJECT

public:
    explicit gamewidget(QWidget *parent = 0);
    ~gamewidget();
public slots:
void left_click();
void right_click();
void up_click();
void down_click();
void start_click();
void return_click();
void timeoutslot();
signals:
void UpSignal();
void DownSignal();
void LeftSignal();
void RightSignal();
private:
    Ui::gamewidget *ui;
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    int directioin;
    int snake[120][2];
    int snake_back[120][2];
    int foodx,foody;
    int foodcount;
    int speed;
    bool suicide,thesame;
    QSound * sound_eat,*sound_die;
    QTimer* timer;
    QPushButton* left_button;
    QPushButton* right_button;
    QPushButton* up_button;
    QPushButton* down_button;
    QPushButton* start_button;
    QPushButton* return_button;
};

#endif // GAMEWIDGET_H
