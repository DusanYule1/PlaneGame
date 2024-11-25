#include "bossgun.h"

BossGun::BossGun(QRect rect,QString Gunpic,bool gunShoot,int gunHealth,QWidget* parent)
{
    this->GunLabel.setGeometry(rect);
    this->GunLabel.setPixmap(QPixmap(Gunpic).scaled(rect.width(),rect.height(),Qt::KeepAspectRatio));
    this->gunShoot = gunShoot;
    this->gunHealth = gunHealth;
    this->GunLabel.setParent(parent);
}

void BossGun::show()
{
    this->GunLabel.show();
}

void BossGun::hide()
{
    this->GunLabel.hide();
}

void BossGun::setGeometry(QRect* rect)
{
    this->GunLabel.setGeometry(*rect);
}

