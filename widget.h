#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include <QPropertyAnimation>
#include <QPushButton>
#include "config.h"
#include "counter.h"
#include "soundthread.h"
#include "myplane.h"
#include "enemy.h"
#include "bullet.h"
#include "makeenemybullet.h"
#include "explosion.h"
#include "boss1.h"
#include "boss2.h"
#include "item.h"
#include "form.h"
#include "mybutton.h"
#include "boss_explosion.h"
#include "setting.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void sendstr(QString s);

public:
    explicit Widget(QWidget *parent = 0);
    int calculate_score(int enemy_health);

    ~Widget();



    MyPlane* myPlane = NULL;


    QString map[3] = {":/new/prefix1/res/map_3.png",":/new/prefix1/res/map_1.png",":/new/prefix1/res/map_2.png"};

    QString shootSound[BULLET_TYPE + 1] = {"",
                                           "qrc:/new/prefix1/res/attack_1.wav",
                                           "qrc:/new/prefix1/res/attack_4.wav",
                                           "qrc:/new/prefix1/res/attack_3.wav",
                                           "qrc:/new/prefix1/res/attack_2.wav"
                                          };
    int music_index = 0;
    QString music[3] = {"qrc:/new/prefix1/res/mus_1.wav",
//                        "qrc:/new/prefix1/res/mus_2.wav",
                        "qrc:/new/prefix1/res/mus_3.wav",
                        "qrc:/new/prefix1/res/mus_4.wav"};


public slots:
    void init();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);



private slots:
    void generateExplosion(int x ,int y);
    void generateBossExplosion(int x ,int y);
    void scrollBackground();//屏幕滚动
    void generateEnemy();//生成敌人
    void moveEnemies();//移动敌人
    void moveBullets();//移动子弹
    void moveEnemyBullets();//移动敌人子弹
    void moveExplosions();//移动爆炸
    void moveBossExplosions();
    void moveItems();
    void checkBulletHit();//检查子弹击中
    void checkBulletHitBoss1();
    void checkBulletHitBoss2();
    void generateBullet();//生成子弹
    void generateItem(int x, int y, int enemyType);//生成道具
    void checkPlaneCrash();//检测碰撞事件
    void checkEnemyBulletHit();//检查敌人子弹击中
    void checkDeath();//检查死亡
    void checkGetItem();
    void getItem(int type);
    void generateEnemyBullet();

    void rightButtonClicked();
    void leftButtonClicked();
    void startButtonClicked();
    void gameOverClicked();
    void settingButtonClicked();
    void pauseButtonClicked();

//    void healthBarUpdate();


    void timersStart();
    void timersStop();


private:
    void showMainMenu();

    void failDoubleClick();
    void specicalRevival();

    void levelMode();

    void generateBossType_1();
    void removeDeadBoss1(Boss1* boss);

    void generateBossType_2();
    void removeDeadBoss2(Boss2* boss);


    double calculateAngleBetweenPoints(int x1, int y1, int x2, int y2); //计算角度用




    Ui::Widget *ui;
    Setting* setting = NULL;
    //Form f;
    int score = 0;//分数
    double scrollOffset = -WINDOW_H; // 滚动偏移量
    QTimer* backgrondSrollTimer; // 屏幕滚动定时器
    myButton* chatButton = NULL;
    QStringList PlaneImagePaths;//飞机存储路径
    int currentPlaneImageIndex = 1; // 当前显示的图片索引
    bool unstart = 1;//记录 开始游戏 有没有被按
    QPoint lastPos; //移动飞机用
    QPoint startPos;//移动飞机用

    QPixmap background_image;//背景图



    QTimer* bulletMoveTimer; // 子弹移动的定时器
    QTimer* bulletGeneratorTimer;//子弹生成的定时器

    QList<Enemy*> enemies; // 存储敌机的列表
    QTimer* enemyMoveTimer; // 敌机移动的定时器
    QTimer* enemyGeneratorTimer; // 敌机生成定时器

    QList<makeEnemyBullet*> enemyBullets; // 存储敌人子弹的列表
    QTimer* enemyBulletMoveTimer; // 敌人子弹移动的定时器

    QList<item*> items;
    QTimer* itemMoveTimer = NULL;

    QList<Explosion*> explosions;
    QList<Boss_explosion*> bossExplosions; // 存储爆炸的列表
    QTimer* explosionMoveTimer = NULL; // 爆炸移动的定时器

    QList<Soundthread*>Sounds;
    QTimer* deleteSoundTimer = NULL;

    QTimer* checkTimer;//检查事件

    QTimer* lockTimer = NULL;//敌人锁定

    QTimer* enemyBulletGenerateTimer;

    QLabel labelStart;//开始游戏label
    //QLabel labelLeftChoose;//左键label
    myButton* leftChoose = NULL;
    myButton* rightChoose = NULL;
    myButton* startButton = NULL;
    myButton* gameOver = NULL;
    myButton* settingButton = NULL;
    myButton* pauseButton = NULL;

//    QLabel labelSetting;//设置键label

   // QLabel labelGameOver;//游戏结束图标

    //设置界面相关//
    bool inSetting = false;//是否在设置界面里
    QLabel labelSettingTitle;
    //设置界面的按钮
    QPushButton openHealthBar;
    QPushButton openScoreBoard;
    QPushButton openSound;
    QPushButton changeModeButton;
    QPushButton changeBackgrond;    //背景改变
    QPushButton changeShootingMode; //射击模式按钮
    bool ifOpenHealthBar = 1;
    bool ifOpenScoreBoard = 1;
    bool ifOpenSound = 1;
    bool ifDebugMode = 0;
    bool ifAutoShoot = 1;


    //关卡相关
    QTimer* timeClick; // 用来记录时间
    int presentTime;

    QTimer* myPlaneDeathCheck = NULL;
    QList<QTimer*> timers;  //timer的总的列表
    QList<QTimer*> presentTimers; //当前使用的timers

    bool ifInPause = 0;


    //用于双击检测
    QTimer* doubleClickTimer;
    QPoint lastClickPos;
    bool isDoubleClick;

    counter* mycounter = nullptr;

    Soundthread* mainMusicThread = NULL;
    Soundthread* mainMusicThread2 = NULL;
    Soundthread* bossMusicThread = NULL;

    QString userInput; // 用于记录用户的输入

    QPropertyAnimation *valueChangeAnimation;


    Boss1* nowBoss1 = nullptr;

    Boss2* nowBoss2 = nullptr;

    //难度成长
    double healthAddRate = 1;
    double attackRate = 1;

    bool boss2Out = 0;
    bool checkBoss2Death = 0;
    bool boss1Out = 0;
    bool checkBoss1Death = 0;

    int fixedRange = 0;
};

#endif // WIDGET_H
