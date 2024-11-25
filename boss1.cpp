#include "boss1.h"
#include "config.h"
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QProgressBar>

Boss1::Boss1(QWidget *parent,QObject* Obj_parent) : QObject(Obj_parent)
{
    init();
    this->parent = parent;
    container.setParent(this->parent);
    container.resize(800, 380);
    bossLeftBody.setParent(&container);
    bossRightBody.setParent(&container);
    bossMiddleBody.setParent(&container);
    bossHealthBar.setParent(&container);

    bossHealthBar.setFixedSize(350, 10);
    bossHealthBar.move(225, 0);
    bossHealthBar.setRange(0, bodyHealth);
    bossHealthBar.setValue(bodyHealth); // 设置初始血量值
    bossHealthBar.setStyleSheet("QProgressBar { border: 1px solid gray; border-radius: 5px; background: white; }"
                             "QProgressBar::chunk { background: red; }");
    bossHealthBar.setOrientation(Qt::Horizontal); // 设置为水平方向
    bossHealthBar.setFormat(""); // 设置显示格式为空字符串
    bossHealthBar.hide();

    bossMiddleBody.setPixmap(QPixmap(":/new/prefix1/res/boss_middle.png"));
    bossMiddleBody.setGeometry(225, 24, 350, 335);
    bossLeftBody.setPixmap(QPixmap(":/new/prefix1/res/boss_left.png").scaled(QSize(225, 205), Qt::KeepAspectRatio));
    bossLeftBody.setGeometry(0, 66, 225, 205);
    bossRightBody.setPixmap(QPixmap(":/new/prefix1/res/boss_right.png").scaled(QSize(225, 205), Qt::KeepAspectRatio));
    bossRightBody.setGeometry(575, 66, 225, 205);

    bossLeftGun = new BossGun(QRect(170, 240, 67, 97),":/new/prefix1/res/boss1_leftGun.png",true,1800,&container);
    bossRightGun = new BossGun(QRect(565, 240, 67, 97),":/new/prefix1/res/boss1_rightGun.png",false,1800,&container);
}

void Boss1::moveBoss()
{
    container.move(container.x(), container.y() + 1);
}

void Boss1::setHealthRate(int healthAddRate)
{
    this->bodyHealth *= healthAddRate;
    this->bossHealthBar.setRange(0, this->bodyHealth);
    this->bossHealthBar.setValue(this->bodyHealth);
    this->leftGunHealth *= healthAddRate;
    this->rightGunHealth *= healthAddRate;
}

void Boss1::setDefenseRate(int heroPlaneType,int rate)
{
    this->def[2] = bulletBasicPower[heroPlaneType-1] * 0.95 * rate;
    this->def[1] = bulletBasicPower[heroPlaneType-1] * 0.75 * rate;
    leftGunHealth *= nowPlaneType;
    rightGunHealth *= nowPlaneType;
}

void Boss1::show()
{
    this->isDead = false;
    bossLeftBody.show();
    bossRightBody.show();
    bossMiddleBody.show();
    bossLeftGun->show();
    bossRightGun->show();
    container.move(0, -400);
    container.lower();
    container.show();
}

void Boss1::hide()
{
    // 隐藏BOSS及其子元素
    container.hide();
    bossLeftGun->hide();
    bossRightGun->hide();
    bossMiddleBody.hide();
    bossLeftBody.hide();
    bossRightBody.hide();
}

void Boss1::init()
{
    connect(this,&Boss1::stop,this,&Boss1::pause);
    connect(this,&Boss1::start,this,&Boss1::Continue);
    movetimer = new QTimer; //BOSS出场移动
    movetimer->start(8);
    connect(movetimer, &QTimer::timeout,
            [=](){
        if(container.y() < 0){
            moveBoss();
        }else{
            movetimer->stop();
            presentTimers.removeOne(movetimer);
            HitCheck->start(10);
            presentTimers.append(HitCheck);
            bossHealthBar.show();
            connect(this, &Boss1::lock,
                    [=](int x,int y,QList<makeEnemyBullet*>* enemyBullets){
                        this->enemyBullets = enemyBullets;
                        this->targrtx = x;
                        this->targety = y;
                        this->leftGunShoot = !this->leftGunShoot; //做到交替射击
                        if(this->leftGunShoot && this->bossLeftGun->gunHealth>0){
                            shoot(this->bossLeftGun,targrtx,targety);
                        }
                        this->rightGunShoot = !this->rightGunShoot;
                        if(this->rightGunShoot && this->bossRightGun->gunHealth >0){
                            shoot(this->bossRightGun ,targrtx,targety);
                        }
           });
        }
    });
}

void Boss1::shoot(BossGun* Gun,int x ,int y)
{
    double angle = calculateAngleBetweenPoints(
                    Gun->GunLabel.x(),
                    Gun->GunLabel.y() + 40,
                    x,
                    y);
    makeEnemyBullet* mybullet = new makeEnemyBullet(
                                Gun->GunLabel.x(),
                                Gun->GunLabel.y()+40,
                                100*nowPlaneType,
                                QPixmap(":/new/prefix1/ImgBox/boss_fire.png").scaled(50, 50, Qt::KeepAspectRatio),
                                5,
                                angle,
                                this->parent
                                );
    // 将子弹添加到列表中
    enemyBullets->append(mybullet);
}

double Boss1::calculateAngleBetweenPoints(int x1, int y1, int x2, int y2)
{
    // 计算两点之间的角度，以弧度为单位
    double angleRadians = qAtan2(y1 - y2, x2 - x1);
    // 将弧度转换为度数
    double angleDegrees = qRadiansToDegrees(angleRadians);
    return angleDegrees;
}

void Boss1::gunGetHit(BossGun* Gun,int power)
{
    Gun->gunHealth -= power;
    if(Gun->gunHealth <= 0){
        Gun->hide();
        defLevel--;
    }
}

void Boss1::pause()
{
    for(int i = 0 ; i < presentTimers.size();i ++){
        presentTimers.at(i)->stop();
    }
}

void Boss1::Continue()
{
    for(int i = 0 ; i < presentTimers.size();i ++){
        presentTimers.at(i)->start();
    }
}
