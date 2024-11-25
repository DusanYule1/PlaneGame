#include "launcher.h"
#include "ui_launcher.h"
#include "config.h"
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QPalette>
#include <QDebug>
#include <QUrl>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "widget.h"

Launcher::Launcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);

    setWindowTitle("Starting... >_<");

    thread = new Soundthread(this);
    this->setFixedSize(WINDOW_W,WINDOW_H);
    this->setStyleSheet("background-color:black;");
    QMediaPlayer* player = new QMediaPlayer;

    QVideoWidget* videoWidget = new QVideoWidget(this);
    videoWidget->setFixedSize(WINDOW_W-400,WINDOW_H);
    videoWidget->move(200,0);
    player->setVideoOutput(videoWidget);
    player->setMedia(QMediaContent(QUrl::fromLocalFile("./ICON.mp4")));
    videoWidget->show();
    player->play();
    connect(player,&QMediaPlayer::stateChanged,this,&Launcher::paintIcon);
    connect(this,&Launcher::widgetInit,&w,&Widget::init);

}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::paintIcon(QMediaPlayer::State state)
{
    QLabel* m = new QLabel(this);
    m->setPixmap(QPixmap(":/new/prefix1/res/R-C.jpg"));
    m->setFixedSize(1200,750);
    m->move(0,(WINDOW_H - 750)/2);
    m->show();
    QLabel* l = new QLabel(this);
    l->setPalette(QPalette(QColor(0,0,0)));
    l->setFixedSize(WINDOW_W,WINDOW_H);
    l->show();

    QLabel* ene1 = new QLabel(this);
    int w1 = 200,h1 = 110;
    ene1->setPixmap(QPixmap(":/new/prefix1/res/s2.png").scaled(w1,h1,Qt::KeepAspectRatio));
    ene1->setStyleSheet("background-color:transparent;");

    ene1->setFixedSize(w1,h1);
    ene1->move(WINDOW_W+50,-40);

    QLabel* ene2 = new QLabel(this);
    int w2 = 200,h2 = 133;
    ene2->setPixmap(QPixmap(":/new/prefix1/res/s6.png").scaled(w2,h2,Qt::KeepAspectRatio));
    ene2->setStyleSheet("background-color:transparent;");
    ene2->setFixedSize(w2,h2);
    ene2->move(-50 - w2, - 100);


    QLabel* title = new QLabel(this);
    int w3 = 473,h3 = 212;
    title->setPixmap(QPixmap(":/new/prefix1/res/title.png").scaled(w3,h3,Qt::KeepAspectRatio));
    title->setStyleSheet("background-color:transparent;");
    title->setFixedSize(w3,h3);
    title->move(WINDOW_W/2 - w3/2, WINDOW_H + 200);

    QLabel* press = new QLabel(this);
    press->setPixmap(QPixmap(":/new/prefix1/res/enter.png").scaled(339,39,Qt::KeepAspectRatio));
    press->hide();
    press->move(WINDOW_W/2 - 339/2,WINDOW_H*2/3 - 39/2);

    QTimer* t = new QTimer(this);
    QTimer* gala = new QTimer(this);
    QTimer* ene = new QTimer(this);
    QTimer* titl = new QTimer(this);
    connect(titl,&QTimer::timeout,this,[=](){
        h += 2;
        title->move(WINDOW_W/2 - w3/2, WINDOW_H + 200 - h);
        if(h >= WINDOW_H/2+300){

            titl->stop();
            press->show();
        }
    });
    connect(ene,&QTimer::timeout,this,[=](){
        enex--,eney--;
        ene1->move(WINDOW_W +50 + enex,- 40  - eney);
        ene2->move(-50 - w2 - enex,  - h2 - eney);
      //  qDebug()<<ene1->x()<<ene1->y();
        if(eney <= -WINDOW_H/2+200)
            ene->stop();
    });

    connect(gala,&QTimer::timeout,this,[=](){
        x2-=1;
        m->move(x2,(WINDOW_H - 750)/2);
        if(x2 <= -1200+WINDOW_W){
            gala->stop();
            ene->start(15);
            titl->start(15);
            title->show();
            ene2->show();
            ene1->show();

        }
    });
    t->setSingleShot(true);
    QTimer* s = new QTimer(this);
    connect(s,&QTimer::timeout,this,[=](){
        x += 3;
        l->move(x,0);
        if(x > WINDOW_W){
            s->stop();
            gala->start(20);
        }
        if(x == 600){
            thread->effect.setLoopCount(QSoundEffect::Infinite);
            thread->play("qrc:/new/prefix1/res/1.01.wav");

        }
    });
    connect(t,&QTimer::timeout,this,[=](){s->start(10);});
    t->start(1000);
}

void Launcher::keyPressEvent(QKeyEvent *event)
{
    //qDebug()<<event->key();
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        thread->setVolume(0);
        thread->effect.stop();
        this->close();
        w.show();
        emit this->widgetInit();
    }
}
