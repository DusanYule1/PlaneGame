#ifndef MYPLANE_H
#define MYPLANE_H

#define PLANE_SMALL 1
#define PLANE_MIDDLE 2
#define PLANE_HUGE 3

#include <QLabel>
#include <QList>
#include <QWidget>
#include <QProgressBar>
#include "bullet.h"
#include <qpropertyanimation.h>
#include <QObject>

class MyPlane
{

public:
    MyPlane(QWidget* parent);
    void moveBullets();
    bool shoot(double attackRate);
    void healthChange(int startValue, int endValue);
    void setType(int type);
    void moveTo(int x,int y);
    void moveTo(QPoint p);
    void generateBullet(int x,int y,int b_type,double attackRate);
    void setMaxHealthIndex(int MaxHealthIndex);
    void setHealth(int health);
public:
    QPropertyAnimation* valueChangeAnimation = NULL;

    QWidget* parent = Q_NULLPTR;
    QList<Bullet*> bullets; // 存储子弹的列表
    QLabel labelPlane;
    int health;
    int cannon_interval = 2;
    int type = PLANE_SMALL;
    int maxHealth;
    bool dead = false;
    bool getDamageBullet = false;
    QProgressBar healthBar;
    QString planePic[4] = {"",
                           ":/new/prefix1/ImgBox/mineplane_1.png",
                           ":/new/prefix1/ImgBox/mineplane_2.png",
                           ":/new/prefix1/res/hero_2.png"};
    QSize planeSize[4] = {QSize(0,0),
                          QSize(PLANE_1_W,PLANE_1_H),
                          QSize(PLANE_2_W,PLANE_2_H),
                          QSize(PLANE_3_W,PLANE_3_H)};

private:
    int planeHealth[4] = {0,1000,1500,1700};
};

#endif // MYPLANE_H
