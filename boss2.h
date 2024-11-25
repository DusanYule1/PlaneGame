#ifndef BOSS2_H
#define BOSS2_H

#include "config.h"
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QObject>
#include <QProgressBar>
#include <QTimer>
#include "makeenemybullet.h"
#include <QList>

class Boss2 : public QObject
{
    Q_OBJECT
public:
    QWidget* parent = NULL;
    QLabel BossPlane;
    int health;
    int def;
    bool leftMoving = 0;
    bool rightMoving = 0;
    bool ifShoot = 1;
    bool isDead = false;
    int nextX = 200; //随意数字

    QTimer* movetimer; //BOSS出场移动

    QTimer* randomMove;
    QList<makeEnemyBullet*>* enemyBullets = NULL;
    QTimer* checkHit;
    QList<QTimer*> presentTimers;
    QTimer* tickTimer;

signals:
    void begin(QList<makeEnemyBullet*>* enemyBullets);
    void start();
    void stop();

public:
    Boss2(QWidget* parent,QObject* Obj_parent = Q_NULLPTR);
    void showUpBoss();
    void randomCrossMoveBoss();
    void setHealthRate(int rate = 1);
    void show();
    void hide();

public slots:
    void pause();
    void Continue();
private:
    void init();
    void Move();
    void shoot();

};

#endif // BOSS2_H
