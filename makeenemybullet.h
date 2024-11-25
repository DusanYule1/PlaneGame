#ifndef MAKEENEMYBULLET_H
#define MAKEENEMYBULLET_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
class makeEnemyBullet
{
public:
    makeEnemyBullet(int x ,int y,int power,QPixmap pixmap,int speed,int angle = 270,QWidget* parent = NULL);
    ~makeEnemyBullet();
    QLabel bullet;
    int power;
    double angle = 0;
    int speed = 0;

};

#endif // MAKEENEMYBULLET_H
