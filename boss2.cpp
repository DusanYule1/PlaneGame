#include "boss2.h"
#include "config.h"
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QProgressBar>

Boss2::Boss2(QWidget *parent,QObject* Obj_parent) : QObject(Obj_parent)
{
    this->parent = parent;
    BossPlane.setParent(parent);
    BossPlane.setPixmap(QPixmap(":/new/prefix1/ImgBox/Boss2.png").scaled(QSize(400, 300), Qt::KeepAspectRatio));
    BossPlane.show();
    BossPlane.move(WINDOW_W/2 - BossPlane.width()/2, -BossPlane.height());
    health = 4000;    //血量设置
    init();
}

void Boss2::init()
{

    connect(this,&Boss2::stop,this,&Boss2::pause);
    connect(this,&Boss2::start,this,&Boss2::Continue);

    movetimer = new QTimer; //BOSS出场移动
    randomMove = new QTimer;
    checkHit = new QTimer;
    tickTimer = new QTimer;

    connect(this,&Boss2::begin,this,[=](QList<makeEnemyBullet*>* enemyBullets){
        this->enemyBullets = enemyBullets;
        movetimer->start(6);});
    presentTimers.append(movetimer);

    connect(movetimer, &QTimer::timeout,
            [=](){
        if(BossPlane.y() < 0){
            showUpBoss();
        }
        else{
            movetimer->stop();
            presentTimers.removeOne(movetimer);
            randomMove->start(8);
            presentTimers.append(randomMove);
            checkHit->start(10);
            presentTimers.append(checkHit);
        }
    });

    connect(randomMove,&QTimer::timeout,this,&Boss2::Move);

    connect(tickTimer, &QTimer::timeout,
            [=](){
            qDebug()<<1;
        static int timess = 0;
        timess++;
        if(timess >= 2){
            timess = 0;
            nextX = qrand()%(WINDOW_W - BossPlane.width());
            if(nextX > BossPlane.x()){
                rightMoving = 1;
            }
            else{
                leftMoving = 1;
            }
            tickTimer->stop();
            presentTimers.removeOne(tickTimer);
        }
    });


}

void Boss2::setHealthRate(int rate)
{
    this->health *= rate;
}

void Boss2::Move()
{

    if(rightMoving && ifShoot == 0){
        if(nextX > BossPlane.x()){
            BossPlane.move(BossPlane.x() + 1, BossPlane.y() );
        }
        else{
            rightMoving = 0;
            ifShoot = 1;
        }
    }else if(leftMoving && ifShoot == 0){
        if(nextX < BossPlane.x()){
            BossPlane.move(BossPlane.x() - 1, BossPlane.y() );
        }
        else{
            leftMoving = 0;
            ifShoot = 1;
        }
    }else if(ifShoot && leftMoving == 0 && rightMoving == 0){
        shoot();
        tickTimer->start(800);
        presentTimers.append(tickTimer);
        ifShoot = 0;
    }
}

void Boss2::shoot()
{
    makeEnemyBullet* mybullet1 = new makeEnemyBullet(
                BossPlane.x() + 60,
                BossPlane.y() + BossPlane.height() - 30,
                250,
                QPixmap(":/new/prefix1/ImgBox/Boss2_bomb.png").scaled(60, 60, Qt::KeepAspectRatio),
                4,
                -90,
                this->parent);
    enemyBullets->append(mybullet1);

    makeEnemyBullet* mybullet2 = new makeEnemyBullet(
                BossPlane.x() +BossPlane.width()  - 100,
                BossPlane.y() + BossPlane.height() - 30,
                250,
                QPixmap(":/new/prefix1/ImgBox/Boss2_bomb.png").scaled(60, 60, Qt::KeepAspectRatio),
                4,
                -90,
                this->parent);
    enemyBullets->append(mybullet2);

}

void Boss2::showUpBoss()
{
    BossPlane.move(BossPlane.x(), BossPlane.y() + 1);
}

void Boss2::randomCrossMoveBoss()
{
    //仅仅做移动
}

void Boss2::show()
{
    this->BossPlane.show();
}

void Boss2::hide()
{
    this->BossPlane.hide();
}

void Boss2::pause()
{
    for(int i = 0 ; i < presentTimers.size();i ++){
        presentTimers.at(i)->stop();
    }
}

void Boss2::Continue()
{
    for(int i = 0 ; i < presentTimers.size();i ++){
        presentTimers.at(i)->start();
    }
}
