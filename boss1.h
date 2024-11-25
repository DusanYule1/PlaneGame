#ifndef BOSS1_H
#define BOSS1_H

#include "config.h"
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QObject>
#include <QProgressBar>
#include <QTimer>
#include <QObject>
#include <qmath.h>
#include "makeenemybullet.h"
#include "bossgun.h"

class Boss1 : public QObject
{
    Q_OBJECT
public:
    Boss1(QWidget* parent,QObject *Obj_parent = Q_NULLPTR);

    QLabel bossLeftBody;
    QLabel bossRightBody;
    QLabel bossMiddleBody;
    BossGun* bossLeftGun = NULL;
    BossGun* bossRightGun = NULL;
    QProgressBar bossHealthBar;

    QWidget container;
    QWidget* parent = NULL;

    int leftGunHealth = 2000;
    int rightGunHealth = 2000;
    int bodyHealth = 6000;

    int defLevel = 2;
    int def[3] = {0, 60, 80} ;

    int bulletBasicPower[3] = {200,250,500};

    int addDamage = 0;

    bool leftGunShoot = 1;
    bool rightGunShoot = 0;
    bool isDead = true;

    int nowPlaneType = 1;

    int targrtx = 0,targety = 0;

    QTimer* movetimer;
    QTimer* HitCheck;
    QList<QTimer*> presentTimers;
    QList<makeEnemyBullet*>* enemyBullets = NULL;

signals:
    void lock(int x,int y,QList<makeEnemyBullet*>* enemyBullets);
    void stop();
    void start();

public slots:
    void moveBoss();
    void pause();
    void Continue();

public:
    void setHealthRate(int rate = 1);
    void setDefenseRate(int heroPlaneType,int rate = 1);
    void show();
    void hide();
    void gunGetHit(BossGun* Gun,int power);

private:
    void init();
    void shoot(BossGun* Gun,int x ,int y);
    double calculateAngleBetweenPoints(int x1, int y1, int x2, int y2);
};

#endif // BOSS1_H
