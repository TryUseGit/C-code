#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<QPainter>
#include<QCursor>
#include<QBrush>
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#define ROW 18
#define COL 28
class Gamewidget : public QWidget
{
    Q_OBJECT
public:
    explicit Gamewidget(QWidget *parent = 0);
    ~Gamewidget();
//    void initgame();
//private:
   QPainter *painter;
   QCursor* cursor;
//   QBrush brush;
   void paintEvent(QPaintEvent*);
   void mousePressEvent(QMouseEvent *);
   bool winjudge();
   int player, pos_x, pos_y;
   int chessboard[ROW][COL];
public slots:
   void winning();
signals:
   void win();
};

#endif // GAMEWIDGET_H
