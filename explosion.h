#ifndef EXPLOSION_H
#define EXPLOSION_H

#define EXPLOSION_NORMAL 0
#define EXPLOSION_BOSS 1

#include <QLabel>
#include <QWidget>
#include "config.h"

class Explosion
{
public:
    Explosion(QWidget* parent = Q_NULLPTR,int x = 0,int y = 0);
    void explode();
    QLabel explosion;
    int explode_index = 1;//爆炸图片序号
    QWidget* parent = NULL;
    int explode_map_num = 4;
    int type = 0;
    QString explode_map[4] = {"",
                              ":/new/prefix1/res/explode_1.png",
                              ":/new/prefix1/res/explode_2.png",
                              ":/new/prefix1/res/explode_3.png"};
    QSize explosion_size[4] = {QSize(0,0),
                           QSize(EXPLODE_1_W,EXPLODE_1_W),
                           QSize(EXPLODE_2_W,EXPLODE_2_W),
                           QSize(EXPLODE_3_W,EXPLODE_3_W)
                           };

};

#endif // EXPLOSION_H
