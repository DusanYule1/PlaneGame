#include "bullet.h"
#include "config.h"
#include "widget.h"
#include <QPixmap>
#include <qmath.h>


Bullet::Bullet(QWidget* parent,int x ,int y,int type,double attackRate)
{
    this->bullet.setParent(parent);
    this->setType(type, attackRate);
    this->bullet.move(x - this->bulletSize[this->type].width()/2,y);
  //  qDebug()<<x<<y;
    this->bullet.show();
    this->bullet.lower();
}

void Bullet::setType(int type,double attackRate)
{
    this->type = type;
    QPixmap bulletPixmap(bulletPic[this->type]);
    // 旋转图片
    QPixmap rotatedBulletPixmap = bulletPixmap.transformed(QMatrix().rotate(0));    //能设置角度
    this->power = bulletPower[this->type]*attackRate;
    this->bullet.setPixmap(QPixmap(bulletPic[this->type]).scaled(bulletSize[this->type], Qt::KeepAspectRatio));

}
