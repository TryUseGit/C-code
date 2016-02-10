#include "gamewidget.h"
#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3
#define COL 10
#define ROW 10
gamewidget::gamewidget(QWidget *parent) :
    QDialog(parent)
{
    //background
    this->setAutoFillBackground(true);
    this->resize(391,220);
    this->setWindowTitle("snack");
    QPalette  palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/img/green.jpg")));
    this->setPalette(palette);
    //button
    left_button = new QPushButton("Left",this);
    left_button->setGeometry(QRect(260,70,40,30));
    right_button = new QPushButton("Right",this);
    right_button->setGeometry(QRect(340,70,40,30));
    up_button = new QPushButton("Up",this);
    up_button->setGeometry(QRect(300,40,40,30));
    down_button = new QPushButton("Down",this);
    down_button->setGeometry(QRect(300,70,40,30));
    start_button = new QPushButton("Start",this);
    start_button->setGeometry(270,120,50,30);
    return_button = new QPushButton("Return",this);
    return_button->setGeometry(330,120,50,30);
    //signal and slot
    connect(left_button,SIGNAL(clicked()),this,SLOT(left_click()));
    connect(right_button,SIGNAL(clicked()),this,SLOT(right_click()));
    connect(up_button,SIGNAL(clicked()),this,SLOT(up_click()));
    connect(down_button,SIGNAL(clicked()),this,SLOT(down_click()));
    connect(start_button,SIGNAL(clicked()),this,SLOT(start_click()));
    connect(return_button,SIGNAL(clicked()),this,SLOT(return_click()));
    //key singnal
    connect(this,SIGNAL(UpSignal()),this,SLOT(up_click()));
    connect(this,SIGNAL(DownSignal()),this,SLOT(down_click()));
    connect(this,SIGNAL(LeftSignal()),left_button,SLOT(click()));
    connect(this,SIGNAL(RightSignal()),right_button,SLOT(click()));
    //auto update
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeoutslot()));
    //rand seed
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    //head
    snake[0][0] = qrand()%ROW;
    snake[0][1] = qrand()%COL;
    //data init
    foodcount = 0;
    suicide = false;
    thesame = false;
    speed = 300;
    sound_eat = new QSound(":/sounds/eating.wav",this);
    sound_die = new QSound(":/sounds/gameover.wav",this);
    foodx = qrand()%ROW;
    foody = qrand()%COL;
    while (foodx==snake[0][0]&&foody==snake[0][1]) {
        foodx = qrand()%ROW;
        foody = qrand()%COL;
    }
    directioin = qrand()%4;
}
gamewidget::~gamewidget()
{
    delete timer;
    delete left_button,right_button,up_button,down_button;
    delete sound_eat,sound_die;
}

void gamewidget::left_click()
{
    directioin = LEFT;
}

void gamewidget::right_click()
{
    directioin = RIGHT;
}

void gamewidget::up_click()
{
    directioin = UP;
}

void gamewidget::down_click()
{
    directioin = DOWN;
}

void gamewidget::start_click()
{
    timer->start(speed);
    switch (directioin) {
    case UP:
        --snake[0][1];
        break;
    case DOWN:
        ++snake[0][1];
        break;
    case LEFT:
        --snake[0][0];
        break;
    case RIGHT:
        ++snake[0][0];
        break;
    default:
        break;
    }
    this->update();
}

void gamewidget::return_click()
{
    int ret = QMessageBox::question(this,"warnnint","Are you sure to return",QMessageBox::StandardButton::Yes,QMessageBox::StandardButton::No);
    if(ret=QMessageBox::Yes){
        this->parentWidget()->show();
        delete this;
    }
}

void gamewidget::timeoutslot()
{
    if(snake[0][0]==foodx&&snake[0][1]==foody){        
        sound_eat->play();
        foodx = qrand()%ROW;
        foody = qrand()%ROW;
        ++foodcount;
    }
    for(int i =0;i<=foodcount;++i){
        snake_back[i][0]=snake[i][0];
        snake_back[i][1]=snake[i][1];
    }
    for(int i=foodcount;i>0;--i){
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
    }
    switch(directioin)
    {
    case UP:--snake[0][1];break;
    case DOWN:++snake[0][1];break;
    case LEFT:--snake[0][0];break;
    case RIGHT:++snake[0][0];break;
    }
    for(int i =0;i<=foodcount;++i){
        if(foodx==snake[i][0]&&foody==snake[i][i]){
            thesame = true;
            break;
        }
    }
    while(thesame){
        foodx = qrand()%ROW;
        foody = qrand()%ROW;
        thesame = false;
        for(int i =0;i<=foodcount;++i){
            if(foodx==snake[i][0]&&foody==snake[i][i]){
                thesame = true;
                break;
            }
        }
    }
//suicide judge
if(foodcount){
    for(int i = 1;i<=foodcount;++i){
        if(snake[0][0]==snake[i][0]&&snake[0][1]==snake[i][1]){
            suicide = true;
        }
    }
}
//border judge
    if(suicide||snake[0][0]<0||snake[0][0]>=COL||snake[0][1]<0||snake[0][1]>=ROW){
        sound_die->play();
        timer->stop();
        for(int i =0;i<=foodcount;++i){
            snake[i][0]=snake_back[i][0];
            snake[i][1]=snake_back[i][1];
        }
        int ret = QMessageBox::information(this,"warnning","GameOver",QMessageBox::StandardButton::Ok);
        if(ret=QMessageBox::Ok){
            this->parentWidget()->show();
            this->close();
            delete this;
            return;
        }
    }
    this->update();
}
//drao table
void gamewidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for(int i=0;i<ROW;++i){
        for(int j = 0;j<COL;++j){
            painter.drawRect(QRect(j*20,i*20,20,20));
        }
    }
//draw food
    painter.drawImage(QRectF(foodx*20,foody*20,20,20),QImage(":/new/prefix1/img/apple.png"));
//draw snake head
    switch (directioin) {
    case UP:
        painter.drawImage(QRectF(snake[0][0]*20,snake[0][1]*20,20,20),QImage(":/new/prefix1/img/headup.png"));
        break;
    case DOWN:
        painter.drawImage(QRectF(snake[0][0]*20,snake[0][1]*20,20,20),QImage(":/new/prefix1/img/headdown.png"));
        break;
    case LEFT:
        painter.drawImage(QRectF(snake[0][0]*20,snake[0][1]*20,20,20),QImage(":/new/prefix1/img/headleft.png"));
        break;
    case RIGHT:
        painter.drawImage(QRectF(snake[0][0]*20,snake[0][1]*20,20,20),QImage(":/new/prefix1/img/headright.png"));
        break;
    default:
        break;
    }
//draw body
    for(int i=1;i<foodcount;++i){
        //左下和上右
        if((snake[i][0]==snake[i-1][0] && snake[i][1]<snake[i-1][1]&&
            snake[i][0]<snake[i+1][0] && snake[i][1]==snake[i+1][1])||
            (snake[i][0]<snake[i-1][0] && snake[i][1]==snake[i-1][1]&&
             snake[i][0]==snake[i+1][0] && snake[i][1]<snake[i+1][1])
           )
           painter.drawImage(QRectF(snake[i][0]*20,snake[i][1]*20,20,20),QImage(":/new/prefix1/img/tl_corner.png"));
        //上左和右下
        else if((snake[i][0]>snake[i-1][0] && snake[i][1]==snake[i-1][1]&&
                 snake[i][0]==snake[i+1][0] && snake[i][1]<snake[i+1][1])||
                 (snake[i][0]==snake[i-1][0] && snake[i][1]<snake[i-1][1]&&
                  snake[i][0]>snake[i+1][0] && snake[i][1]==snake[i+1][1])
                )
            painter.drawImage(QRectF(snake[i][0]*20,snake[i][1]*20,20,20),QImage(":/new/prefix1/img/tr_corner.png"));
        //下右和左上
        else if((snake[i][0]<snake[i-1][0] && snake[i][1]==snake[i-1][1]&&
                 snake[i][0]==snake[i+1][0] && snake[i][1]>snake[i+1][1])||
                 (snake[i][0]==snake[i-1][0] && snake[i][1]>snake[i-1][1]&&
                  snake[i][0]<snake[i+1][0] && snake[i][1]==snake[i+1][1])
                )
            painter.drawImage(QRectF(snake[i][0]*20,snake[i][1]*20,20,20),QImage(":/new/prefix1/img/bl_corner.png"));
        //右上和下左
        else if((snake[i][0]==snake[i-1][0] && snake[i][1]>snake[i-1][1]&&
                 snake[i][0]>snake[i+1][0] && snake[i][1]==snake[i+1][1])||
                 (snake[i][0]>snake[i-1][0] && snake[i][1]==snake[i-1][1]&&
                  snake[i][0]==snake[i+1][0] && snake[i][1]>snake[i+1][1])
                )
            painter.drawImage(QRectF(snake[i][0]*20,snake[i][1]*20,20,20),QImage(":/new/prefix1/img/br_corner.png"));
        else if(snake[i][1]==snake[i-1][1]){
            painter.drawImage(QRectF(snake[i][0]*20,snake[i][1]*20,20,20),QImage(":/new/prefix1/img/h_body.png"));
        }
        else if(snake[i][0]==snake[i-1][0]){
            painter.drawImage(QRectF(snake[i][0]*20,snake[i][1]*20,20,20),QImage(":/new/prefix1/img/v_body.png"));
        }
    }
    if(foodcount){
        if(snake[foodcount][0]==snake[foodcount-1][0]&&snake[foodcount][1]>snake[foodcount-1][1])
            painter.drawImage(QRectF(snake[foodcount][0]*20,snake[foodcount][1]*20,20,20),QImage(":/new/prefix1/img/tail.png"));
        else if(snake[foodcount][0]==snake[foodcount-1][0]&&snake[foodcount][1]<snake[foodcount-1][1])
            painter.drawImage(QRectF(snake[foodcount][0]*20,snake[foodcount][1]*20,20,20),QImage(":/new/prefix1/img/taildown.png"));
        else if(snake[foodcount][0]>snake[foodcount-1][0]&&snake[foodcount][1]==snake[foodcount-1][1])
            painter.drawImage(QRectF(snake[foodcount][0]*20,snake[foodcount][1]*20,20,20),QImage(":/new/prefix1/img/tailleft.png"));
        else
            painter.drawImage(QRectF(snake[foodcount][0]*20,snake[foodcount][1]*20,20,20),QImage(":/new/prefix1/img/tailright.png"));
    }
}

void gamewidget::keyPressEvent(QKeyEvent *k)
{
    if(k->key()==Qt::Key_W)
        emit UpSignal();
    else if(k->key()==Qt::Key_S)
        emit DownSignal();
    else if (k->key()==Qt::Key_A)
        emit LeftSignal();
    else if(k->key()==Qt::Key_D)
        emit RightSignal();
}
\
