#ifndef BOSSGUN_H
#define BOSSGUN_H

#include <QLabel>
#include <QRect>
class BossGun
{
public:
    BossGun(QRect rect,QString Gunpic,bool gunShoot,int gunHealth = 1800,QWidget* parent = NULL);
    void show();
    void hide();
    void setGeometry(QRect* rect);
    QLabel GunLabel;
    int gunHealth = 1800;
    bool gunShoot;
};

#endif // BOSSGUN_H
