#include "makeenemybullet.h"
#include "config.h"

makeEnemyBullet::makeEnemyBullet(int x ,int y,int power,QPixmap pixmap,int speed,int angle,QWidget* parent)
{

    bullet.setParent(parent);
    this->power = power;
    bullet.setPixmap(pixmap);
    bullet.move(x, y);
    this->speed = speed;
    bullet.show();
    bullet.lower();
    this->angle = angle;
}

makeEnemyBullet::~makeEnemyBullet()
{

}
