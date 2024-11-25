#ifndef BULLET_H
#define BULLET_H

#define BULLET_TINY 1
#define BULLET_MIDDLE 2
#define BULLET_STRONG 3
#define BULLET_DAMAGE 4

#include <QLabel>
#include <QList>
#include <QWidget>
#include "config.h"

class Bullet
{
public:
    Bullet(QWidget* parent = NULL,int x = 0,int y = 0,int type = BULLET_TINY,double attackRate = 1);
    void setType(int type, double attackRate);

public:
    QLabel bullet;
    QWidget*parent = Q_NULLPTR;
    int power;
    int type = BULLET_TINY; //子弹类型
    QString bulletPic[BULLET_TYPE + 1] = {"",
                           ":/new/prefix1/ImgBox/fire.png",
                           ":/new/prefix1/res/bullet_2.png",
                           ":/new/prefix1/res/bullet_1.png",
                           ":/new/prefix1/ImgBox/fire_damage.png"};
    QSize bulletSize[BULLET_TYPE + 1] = {QSize(0,0),
                           QSize(BULLET_1_W,BULLET_1_H),
                           QSize(BULLET_2_W,BULLET_2_H),
                           QSize(BULLET_3_W,BULLET_3_H),
                           QSize(BULLET_4_W,BULLET_4_H)};


    int bulletPower[BULLET_TYPE + 1] = {0,100,250,500,200};

    double angle = 90; //角度逆时针增大

    bool couldGoThroughEnemy = 0;
    bool ifBulletInEnemy = 0;


};

#endif // MAKEBULLET_H
