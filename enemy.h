#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MIDDLE 1
#define ENEMY_HUGE 2
#define ENEMY_TINY1 3
#define ENEMY_TINY2 4
#define ENEMY_FLAME 5

#include <QLabel>
#include <QSize>
#include <QWidget>
#include "config.h"

class Enemy
{
public:
    Enemy(QWidget* parent = Q_NULLPTR, double healhAddRate = 1);
    void setType();

public:

    QWidget* parent = NULL;
    QLabel enemy;
    int health;
    int enemyType;
    int moveSpeed;
    bool ifFire = 0;
    int enemyHealth[6] = {0,200,500,100,100,300};
    QString enemyImagePaths[6] = {"",
                                  ":/new/prefix1/res/enemy_1.png",
                                  ":/new/prefix1/res/enemy_2.png",
                                  ":/new/prefix1/ImgBox/enemy_1.png",
                                  ":/new/prefix1/ImgBox/enemy_2.png",
                                  ":/new/prefix1/ImgBox/enemy_Flame.png"};
    QSize enemy_size[6] = {QSize(0,0),
                           QSize(ENEMY_1_W,ENEMY_1_H),
                           QSize(ENEMY_2_W,ENEMY_2_H),
                           QSize(ENEMY_3_W,ENEMY_3_H),
                           QSize(ENEMY_4_W,ENEMY_4_H),
                           QSize(ENEMY_5_W,ENEMY_5_H)};

};

#endif // ENEMY_H
