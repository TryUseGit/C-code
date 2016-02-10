#include "gamewidget.h"

Gamewidget::Gamewidget(QWidget *parent) : QWidget(parent),player(1),pos_x(0),pos_y(0)
{
    this->resize(600,400);
    this->setWindowTitle("GoBang");
    this->setAutoFillBackground(true);
    memset(chessboard,0,sizeof(chessboard));
    cursor =  new QCursor();
    connect(this,SIGNAL(win()),this,SLOT(winning()));
}
Gamewidget::~Gamewidget()
{
    delete painter;
}

void Gamewidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    for(int i=2;i<ROW;++i){
        for(int j =2;j<COL;++j){            
                painter->drawRect(QRect(j*20,i*20,20,20));
        }
    }
    for(int i=2;i<ROW;++i){
        for(int j =2;j<COL;++j){
            if(chessboard[i][j]==2)
                painter->drawImage(QRectF(j*20,i*20,20,20),QImage(":/img/img/white_chess.png"));
            else if(chessboard[i][j]==1)
                painter->drawImage(QRectF(j*20,i*20,20,20),QImage(":/img/img/black_chess.png"));
        }
    }
}

void Gamewidget::mousePressEvent(QMouseEvent *event)
{
    pos_x = event->y()/20;
    pos_y=event->x()/20;
//    qDebug()<<pos_x<<pos_y;
    if(pos_x>=2&&pos_x<=ROW&&pos_y>=2&&pos_y<=COL&&chessboard[pos_x][pos_y]==0){
        if (player % 2 == 1) {
            chessboard[pos_x][pos_y] = 2;
            this->update();
            if (winjudge()) {
                emit win();
            }

        }
        else {
            chessboard[pos_x][pos_y] = 1;
            this->update();
            if (winjudge()) {
                emit win();
            }
        }
        ++player;
    }

}

bool Gamewidget::winjudge()
{
    int currentplayer = player % 2 + 1;
        int x, y;
        int flag = 1;
        for (x = pos_x, y = pos_y;x >= 2 && x<ROW;) {
            if (chessboard[++x][y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        for (x = pos_x, y = pos_y;x>2 && x <= ROW;) {
            if (chessboard[--x][y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        if (flag == 5)
            return true;
        flag = 1;
        for (x = pos_x, y = pos_y;y>2 && y <= COL;) {
            if (chessboard[x][--y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        for (y = pos_x, y = pos_y;y >= 2 && y<COL;) {
            if (chessboard[x][++y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        if (flag == 5)
            return true;
        flag = 1;
        for (x = pos_x, y = pos_y;x<ROW&&x >= 2 && y>2 && y <= COL;) {
            if (chessboard[++x][--y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        for (x = pos_x, y = pos_y;x <= ROW&&x>2 && y >= 2 && y<COL;) {
            if (chessboard[--x][++y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        if (flag == 5)
            return true;
        flag = 1;
        for (x = pos_x, y = pos_y;x<ROW&&x >= 2 && y >= 2 && y<COL;) {
            if (chessboard[++x][++y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        for (x = pos_x, y = pos_y;x <= ROW&&x>2 && y>2 && y <= COL;) {
            if (chessboard[--x][--y] == currentplayer) {
                ++flag;
            }
            else
                break;
        }
        if (flag == 5)
            return true;

        return false;
}

void Gamewidget::winning()
{
    if(player==1){
        if(QMessageBox::information(this,"","player 1 win",QMessageBox::StandardButton::Ok)==QMessageBox::Ok){
            this->close();
        }
    }
    else{
        if(QMessageBox::information(this,"","player 2 win",QMessageBox::StandardButton::Ok)==QMessageBox::Ok){
            this->close();
        }
    }
}



