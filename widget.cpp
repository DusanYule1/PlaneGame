#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QSize>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPoint>
#include <QList>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QtMath>
#include <QMatrix>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("**PlaneGame**");//应用窗口名称

    //背景图片
    background_image.load(map[0]);
    setFixedSize(WINDOW_W,WINDOW_H);//设置窗口大小
    backgrondSrollTimer = new QTimer(this);
    connect(backgrondSrollTimer, &QTimer::timeout, this, &Widget::scrollBackground);
    backgrondSrollTimer->setInterval(5); // 调整时间间隔（毫秒）以控制滚动速度
    backgrondSrollTimer->start();

    myPlane = new MyPlane(this);
    //左选择
    leftChoose = new myButton(80,80,150, 779,":/new/prefix1/ImgBox/left.png",this);
    connect(leftChoose,&myButton::clicked,this,&Widget::leftButtonClicked);
    //右选择
    rightChoose = new myButton(80,80,570, 779,":/new/prefix1/ImgBox/right.png",this);
    connect(rightChoose,&myButton::clicked,this,&Widget::rightButtonClicked);
    //开始按钮
    startButton = new myButton(161,43,WINDOW_W/2-161/2,WINDOW_H/2-43/2,":/new/prefix1/ImgBox/lk.png",this);
    connect(startButton,&myButton::clicked,this,&Widget::startButtonClicked);
    //gameOver按钮
    gameOver = new myButton(400, 200,WINDOW_W/2 - 200 , WINDOW_H/2 - 100,":/new/prefix1/ImgBox/GAMEOVER.png",this);
    connect(gameOver,&myButton::clicked,this,&Widget::gameOverClicked);
    //设置按钮
    settingButton = new myButton(80, 80,WINDOW_W - 80, WINDOW_H - 80,":/new/prefix1/ImgBox/setting4.png",this);
    connect(settingButton,&myButton::clicked,this,&Widget::settingButtonClicked);

    //暂停按钮
    pauseButton = new myButton(80, 80,WINDOW_W - 80, 0, ":/new/prefix1/ImgBox/pause.png",this);
    connect(pauseButton,&myButton::clicked,this,&Widget::pauseButtonClicked);
    pauseButton->hide();
    pauseButton->raise();

    //聊天按钮
    chatButton = new myButton(50,50,10,WINDOW_H-60,":/new/prefix1/res/chat.jpg",this);
    //connect(chatButton,&myButton::clicked,this,[=](){f.show();});
    chatButton->hide();

    gameOver->hide();

    //设置飞机初始
    currentPlaneImageIndex = PLANE_SMALL;     //索引
    myPlane->setType(currentPlaneImageIndex);

    //设置显示
    showMainMenu(); // 显示主界面内容

    setting = new Setting(this);
    setting->hide();
    connect(setting,&Setting::shiftMap,this,[=](int map_index){
        qDebug()<<map_index;
        background_image.load(map[map_index]);});
    //timer的初始化

    //双击检测初始化
    doubleClickTimer = new QTimer(this);
    doubleClickTimer->setInterval(250); // 间隔100ms检测双击
    connect(doubleClickTimer, &QTimer::timeout, this, &Widget::failDoubleClick);
    isDoubleClick = false;

    // 创建随机敌机生成定时器
        enemyGeneratorTimer = new QTimer(this);
        connect(enemyGeneratorTimer, &QTimer::timeout, this, &Widget::generateEnemy);
        enemyGeneratorTimer->setInterval(ENEMY_GENERATE_INTERVAL); // 每隔xx毫秒生成一个敌机
        timers.append(enemyGeneratorTimer);

    // 创建关卡计时器
        timeClick = new QTimer(this);
        timeClick->setInterval(100);
        timers.append(timeClick);
        //上面两个不同时加到列表里

    // 创建敌机移动定时器
    enemyMoveTimer = new QTimer(this);
    connect(enemyMoveTimer, &QTimer::timeout, this, &Widget::moveEnemies);
    enemyMoveTimer->setInterval(10); // 每隔xx毫秒移动一次
    timers.append(enemyMoveTimer);

    // 道具移动定时器
    itemMoveTimer = new QTimer(this);
    connect(itemMoveTimer,&QTimer::timeout,this,&Widget::moveItems);
    itemMoveTimer->setInterval(10);
    timers.append(itemMoveTimer);


    // 创建爆炸移动定时器
    explosionMoveTimer = new QTimer(this);
    connect(explosionMoveTimer, &QTimer::timeout, this, &Widget::moveExplosions);
    connect(explosionMoveTimer, &QTimer::timeout, this, &Widget::moveBossExplosions);
    explosionMoveTimer->setInterval(180); // 每隔xx毫秒移动一次
    timers.append(explosionMoveTimer);

    // 创建子弹移动定时器
    bulletMoveTimer = new QTimer(this);
    connect(bulletMoveTimer, &QTimer::timeout, this, &Widget::moveBullets);

    bulletMoveTimer->setInterval(6);
    timers.append(bulletMoveTimer);

    // 创建敌人子弹移动定时器
    enemyBulletMoveTimer = new QTimer(this);
    connect(enemyBulletMoveTimer, &QTimer::timeout, this, &Widget::moveEnemyBullets);
   // connect(enemyBulletMoveTimer, &QTimer::timeout, this, &Widget::moveBossBullets);
    enemyBulletMoveTimer->setInterval(6);
    timers.append(enemyBulletMoveTimer);

    // 创建检查事件定时器
    checkTimer = new QTimer(this);
    connect(checkTimer, &QTimer::timeout, this, &Widget::checkPlaneCrash);//飞机碰撞
    connect(checkTimer, &QTimer::timeout, this, &Widget::checkBulletHit);//子弹射中
    connect(checkTimer, &QTimer::timeout, this, &Widget::checkEnemyBulletHit);//敌人子弹击中
    connect(checkTimer, &QTimer::timeout, this, &Widget::checkDeath);//检测死亡
    connect(checkTimer,&QTimer::timeout,this,&Widget::checkGetItem);//道具检测

    checkTimer->setInterval(10);
    timers.append(checkTimer);

    // 创建子弹生成定时器
    bulletGeneratorTimer = new QTimer(this);
    connect(bulletGeneratorTimer, &QTimer::timeout, this, &Widget::generateBullet);
    bulletGeneratorTimer->setInterval(250); //子弹的生成频率
    timers.append(bulletGeneratorTimer);

    // 创建敌人子弹生成定时器
    enemyBulletGenerateTimer = new QTimer(this);
    connect(enemyBulletGenerateTimer, &QTimer::timeout, this, &Widget::generateEnemyBullet);
    enemyBulletGenerateTimer->setInterval(1500);
    timers.append(enemyBulletGenerateTimer);
}


/*以下为函数区*/
//*****************************//
void Widget::init()
{
    qsrand(QTime::currentTime().msec());
    music_index = qrand()%4;
    mainMusicThread2 = new Soundthread();
    mainMusicThread2->setLoopCount(QSoundEffect::Infinite);
    mainMusicThread2->setVolume(0);
    mainMusicThread2->play(music[music_index]);

    mainMusicThread = new Soundthread();
    mainMusicThread->setLoopCount(QSoundEffect::Infinite);
    mainMusicThread->setVolume(1);
    mainMusicThread->play("qrc:/new/prefix1/res/Player_Select.wav");

    bossMusicThread = new Soundthread();
    bossMusicThread->setLoopCount(QSoundEffect::Infinite);
    bossMusicThread->setVolume(0);
    bossMusicThread->play("qrc:/new/prefix1/res/boss_2.wav");
}

void Widget::timersStart()  //定时器的开启
{
    for(int i=0;i < presentTimers.size();i++){
        presentTimers.at(i)->start();
    }
}

void Widget::timersStop()
{
    for(int i=0;i < presentTimers.size();i++){
        presentTimers.at(i)->stop();
    }
}

void Widget::pauseButtonClicked()
{
    ifInPause = !ifInPause;
    if(ifInPause){
        timersStop();
        backgrondSrollTimer->stop();
        if(nowBoss1 != nullptr){
            if(nowBoss1->isDead == false){
                emit nowBoss1->stop();
            }
        }
        if(nowBoss2 != nullptr){
            if(nowBoss2->isDead == false){
                emit nowBoss2->stop();
            }
        }
    }
    else{
        timersStart();
        backgrondSrollTimer->start();
        if(nowBoss1 != nullptr){
            if(nowBoss1->isDead == false){
                emit nowBoss1->start();
            }
        }
        if(nowBoss2 != nullptr){
            if(nowBoss2->isDead == false){
                emit nowBoss2->start();
            }
        }
    }
}

void Widget::rightButtonClicked()
{
    currentPlaneImageIndex ++;
    while(currentPlaneImageIndex > 3){
        currentPlaneImageIndex -= 3;
    }
    myPlane->setType(currentPlaneImageIndex);
    myPlane->moveTo(WINDOW_W/2 - myPlane->labelPlane.width()/2, 779);
    update();
    //右按键  选择飞机
}

void Widget::leftButtonClicked()
{
    currentPlaneImageIndex += 2;
    while(currentPlaneImageIndex > 3){
        currentPlaneImageIndex -= 3;
    }
    myPlane->setType(currentPlaneImageIndex);
    myPlane->moveTo(WINDOW_W/2 - myPlane->labelPlane.width()/2, 779);
    update();
    //左按键  选择飞机
}

void Widget::startButtonClicked()
{

    if(ifOpenSound){
        mainMusicThread->setVolume(0);
        mainMusicThread2->setVolume(1);
    }

    //设置按钮
    startButton->hide();
    rightChoose->hide();
    leftChoose->hide();
    settingButton->hide();
    pauseButton->show();

    unstart = 0;
    myPlane->dead = false;

    switch (setting->mapIndex()) {
    case 0:
        healthAddRate = 1;
        break;
    case 1:
        healthAddRate = 2;
        break;
    case 2:
        healthAddRate = 3;
        break;
    default:
        healthAddRate = 1;
        break;
    }

    attackRate = 1;

    boss2Out = 0;
    checkBoss2Death = 0;
    boss1Out = 0;
    checkBoss1Death = 0;

    myPlane->setMaxHealthIndex(currentPlaneImageIndex);
    myPlane->health = myPlane->maxHealth;
    myPlane->healthBar.setRange(0, myPlane->maxHealth); // 设置血量范围
    myPlane->healthBar.setValue(myPlane->health); // 设置当前血量

    if(ifDebugMode == 0){
        levelMode();
    }

    enemyGeneratorTimer->setInterval(ENEMY_GENERATE_INTERVAL);

    presentTimers = timers;

    timersStart();

    // 初始化积分器
    mycounter = new counter(this);
    if(ifOpenScoreBoard){
        mycounter->showNum(0);
    }

    // 是否打开血量显示
    if(ifOpenHealthBar)
    {
        myPlane->healthBar.show();
    }

    qsrand(QTime::currentTime().msec());
    music_index = qrand()%4;

    if(ifOpenSound){
        mainMusicThread2->setVolume(1);
        mainMusicThread2->play(music[setting->mapIndex()]);
    }

}

void Widget::gameOverClicked()
{
    if(myPlane->dead == 1 && (unstart == 0)){
        if(nowBoss1 != nullptr && !(nowBoss1->isDead)){
            removeDeadBoss1(nowBoss1);
            nowBoss1->isDead = true;
        }
        if( nowBoss2 != nullptr && !(nowBoss2->isDead) ){
            removeDeadBoss2(nowBoss2);
            nowBoss2->isDead = true;
        }

        unstart = 1;
        score = 0;
        showMainMenu();

        if(ifOpenSound){
            mainMusicThread->setVolume(1);
            mainMusicThread2->setVolume(0);
            mainMusicThread->setLoopCount(QSoundEffect::Infinite);
            mainMusicThread->play("qrc:/new/prefix1/res/Player_Select.wav");
        }
    }
}

void Widget::settingButtonClicked()
{
    if(inSetting){
        pauseButton->hide();
        settingButton->show();
        startButton->show();
        leftChoose->show();
        rightChoose->show();
        myPlane->labelPlane.show();
        setting->hide();
    }else{
        pauseButton->hide();
        settingButton->show();
        startButton->hide();
        leftChoose->hide();
        rightChoose->hide();
        myPlane->labelPlane.hide();
        setting->show();
    }
    inSetting = !inSetting;

    this->ifOpenHealthBar = setting->ifOpenHealthBar;//1;
    this->ifOpenScoreBoard = setting->ifOpenScoreBoard;
    this->ifOpenSound = setting->ifOpenSound;
    this->ifDebugMode = setting->ifDebugMode;
    this->ifAutoShoot = setting->ifAutoShoot;

    if(ifAutoShoot == 0){
        if(timers.contains(bulletGeneratorTimer)){
            timers.removeOne(bulletGeneratorTimer);
        }
    }
    else{
        if(timers.contains(bulletGeneratorTimer) == 0){
            timers.append(bulletGeneratorTimer);
        }
    }
    if(ifDebugMode == 0){
        timers.append(timeClick);
    }

    else{
        if(timers.contains(timeClick)){
            timers.removeOne(timeClick);
        }
    }

    static bool b1 = 1;

    if(ifOpenSound == 0){
        b1 = 0;
    }

    if(ifOpenSound == 0){
        mainMusicThread->effect.setVolume(0);
        mainMusicThread2->effect.setVolume(0);
    }
    else{
        if(ifOpenSound != b1){
            mainMusicThread->effect.setVolume(1);
            mainMusicThread2->effect.setVolume(0);
            mainMusicThread->effect.setLoopCount(QSoundEffect::Infinite);
            mainMusicThread->play("qrc:/new/prefix1/res/Player_Select.wav");
            b1 = 1;
        }
    }
//    //按下设置按键

}

void Widget::showMainMenu()
{
    pauseButton->hide();
    settingButton->show();
    startButton->show();
    leftChoose->show();
    rightChoose->show();
    myPlane->labelPlane.show();
    myPlane->healthBar.hide();
    gameOver->hide();

    myPlane->moveTo(WINDOW_W/2 - myPlane->labelPlane.width()/2, 779);

    timersStop();

    if(myPlane->dead == 1){
        //再做三个函数，清除我方子弹，敌方子弹，敌机，BOSS(?
        while(enemies.size() != 0){     //删除当前敌人
            Enemy* myenemy = enemies.at(0);
            enemies.removeOne(myenemy);
            myenemy->enemy.deleteLater();
        }

        while(myPlane->bullets.size() != 0){        //删除当前子弹
            Bullet* bulllet = myPlane->bullets.at(0);
            myPlane->bullets.removeOne(bulllet);
            bulllet->bullet.deleteLater();
        }

        for(auto e:explosions) {     //删除当前所有爆炸
            e->explosion.setVisible(false);
            delete e;
        }

        while(enemyBullets.size() != 0){        //删除当前敌人子弹
            makeEnemyBullet* bulllet = enemyBullets.at(0);
            enemyBullets.removeOne(bulllet);
            bulllet->bullet.deleteLater();
        }

        for(auto e:items) {     //删除当前所有道具
            e->item_label.setVisible(false);
            delete e;
        }

        delete mycounter;       //删除当前计数器

        myPlane->getDamageBullet = false;
    }
}

void Widget::checkDeath()// 血量扣完，GAMEOVER显示
{
    if(myPlane->dead == 1){
        gameOver->show();
        pauseButton->hide();
        if(ifOpenSound){
            mainMusicThread2->setVolume(0);
        }
    }
    else{
        gameOver->hide();
        pauseButton->show();
    }
}

void Widget::checkPlaneCrash()//检查飞机是否发生碰撞
{
    if(myPlane->dead == 0){
        bool havehit = false;
        for (int i = 0; i < enemies.size(); i++) {
            Enemy* myenemy = enemies.at(i);
            if (myenemy->enemy.geometry().intersects(myPlane->labelPlane.geometry())) {
                enemies.removeOne(myenemy);

                generateExplosion(myenemy->enemy.x(),myenemy->enemy.y());//爆炸动画
                //清除敌机，播放音效
                havehit = true;
                myenemy->enemy.deleteLater();

                //如果碰撞，本机掉血
                myPlane->health -= myenemy->health/healthAddRate;
                //如果本机血量为0，判定死亡
                if(myPlane->health <= 0)
                {

                    Soundthread* thread = new Soundthread();
                    Sounds.append(thread);
                    if(ifOpenSound)
                        thread->play("qrc:/new/prefix1/res/GameOver.wav");

                    myPlane->healthChange(myPlane->health + myenemy->health, 0);
                    bulletGeneratorTimer->stop();//停止发射，但不消失
                    myPlane->dead = 1;

                    //播放完动画再消失
                    connect(myPlane->valueChangeAnimation,
                            QAbstractAnimation::stateChanged,
                            this,
                            [=]()
                         {
                                if(myPlane->dead){
                                    myPlane->labelPlane.hide();
                                    myPlane->healthBar.hide();
                                 }
                         });

                }else
                    myPlane->healthChange(myPlane->health + myenemy->health, myPlane->health);
                break;
            }
        }

        if(havehit){
            Soundthread* thread = new Soundthread();
            Sounds.append(thread);
            if(ifOpenSound)
                thread->play(NORMAL_EXPLOSION_SOUND);
        }
    }
}

void Widget::checkEnemyBulletHit()//检查敌人子弹击中
{
    if(myPlane->dead == 0){

        for (int i = 0; i < enemyBullets.size(); i++) {
            makeEnemyBullet* enemyBullet = enemyBullets.at(i);
            if (enemyBullet->bullet.geometry().intersects(myPlane->labelPlane.geometry())) {
                enemyBullets.removeOne(enemyBullet);

                enemyBullet->bullet.deleteLater();

                //如果碰撞，本机掉血
                myPlane->health -= enemyBullet->power;
                //如果本机血量为0，判定死亡
                if(myPlane->health <= 0)
                {
                    myPlane->healthChange(myPlane->health + enemyBullet->power, 0);
                    bulletGeneratorTimer->stop();//停止发射，但不消失
                    myPlane->dead = 1;
                    //播放完动画再消失
                    connect(myPlane->valueChangeAnimation,
                            QAbstractAnimation::stateChanged,
                            this,
                            [=]()
                         {
                                if(myPlane->dead){
                                    myPlane->labelPlane.hide();
                                    myPlane->healthBar.hide();
                                 }
                         });

                }else
                    myPlane->healthChange(myPlane->health + enemyBullet->power, myPlane->health );
                break;
            }
        }
    }
}

void Widget::checkBulletHit()//检查子弹击中敌机
{
    QList<Bullet*> bulletsToDelete;//将要删除的列表
    QList<Enemy*> enemiesToDelete;

    bool havehit = false;
    // 遍历子弹列表
    for (int i = 0; i < myPlane->bullets.size(); i++) {
        Bullet* mybullet = myPlane->bullets.at(i);     //.at比[]更安全

        // 遍历敌机列表
        for (int j = 0; j < enemies.size(); j++) {
            Enemy* myenemy = enemies.at(j);

            if(mybullet->couldGoThroughEnemy == 0){ //子弹不能贯穿
            // 判断子弹和敌机是否重叠
                if (mybullet->bullet.geometry().intersects(myenemy->enemy.geometry())) {

                    bulletsToDelete.append(mybullet);

                    //生成爆炸
                    generateExplosion(myenemy->enemy.x(),myenemy->enemy.y());

                    havehit = true;

                    //血量检测，如果敌人血量为0，清除

                    myenemy->health -= mybullet->power;
                    if(myenemy->health <= 0){
                        //计算得分
                        calculate_score(myenemy->enemyHealth[myenemy->enemyType] );

                        //显示得分
                        if(ifOpenScoreBoard){
                      //      qDebug()<<"score"<<calculate_score(myenemy->enemyHealth[myenemy->enemyType]);
                            mycounter->showNum(calculate_score(myenemy->enemyHealth[myenemy->enemyType]));
                        }
                        enemiesToDelete.append(myenemy);

                        //几率生成道具
                        generateItem(myenemy->enemy.x(), myenemy->enemy.y(), myenemy->enemyType);
                    }
                    break;
                }
            }
            else{       //子弹可以贯穿
                if (myenemy->enemy.geometry().contains(QPoint(mybullet->bullet.x(), mybullet->bullet.y()))) {

                    if(mybullet->ifBulletInEnemy == 0){
                        //生成爆炸
                        generateExplosion(myenemy->enemy.x(),myenemy->enemy.y());

                        havehit = true;
                        //血量检测，如果敌人血量为0，清除

                        myenemy->health -= mybullet->power;
                        if(myenemy->health <= 0){
                            //计算得分
                            calculate_score(myenemy->enemyHealth[myenemy->enemyType] );

                            //显示得分
                            if(ifOpenScoreBoard){
                                //qDebug()<<"score"<<calculate_score(myenemy->enemyHealth[myenemy->enemyType]);
                                mycounter->showNum(calculate_score(myenemy->enemyHealth[myenemy->enemyType]));
                            }
                            enemiesToDelete.append(myenemy);

                            //几率生成道具
                            generateItem(myenemy->enemy.x(), myenemy->enemy.y(), myenemy->enemyType);

                        }
                        mybullet->ifBulletInEnemy = 1;
                    }

                    break;
                }
                if(j == enemies.size() - 1){
                    mybullet->ifBulletInEnemy = 0;
                }
            }
        }


    }

    if(havehit){
        //播放音效
        Soundthread* thread = new Soundthread();Sounds.append(thread);

        if(ifOpenSound){
            thread->play(NORMAL_EXPLOSION_SOUND);
        }
    }
    // 删除重叠的子弹和敌机
    for (Bullet* mybullet : bulletsToDelete) {
        myPlane->bullets.removeOne(mybullet);
        mybullet->bullet.deleteLater();
    }

    for (Enemy* myenemy : enemiesToDelete) {
        enemies.removeOne(myenemy);
        myenemy->enemy.deleteLater();
    }
}

void Widget::generateExplosion(int x ,int y)//生成爆炸
{
    Explosion* myexplosion = new Explosion(this, x, y);
    explosions.append(myexplosion);
}

void Widget::generateBossExplosion(int x ,int y)
{
    Boss_explosion* explosion = new Boss_explosion(this,x,y);
    bossExplosions.append(explosion);
}

void Widget::generateItem(int x ,int y, int enemyType)
{
    if(enemyType == 200 && myPlane->getDamageBullet == 0){
        item* it = new item(x,y,this,ITEM_DAMAGE);
        it->ifMove = 0;
        items.append(it);
    }
    else{
        int ch = qrand()%10;

        if(enemyType == ENEMY_HUGE){
            if(ch < 5 + setting->mapIndex()){
                int type = qrand()%3 + 2;
                item* it = new item(x,y,this,type);
                items.append(it);
            }
        }else{
            if(ch < 3 + setting->mapIndex() / 2){
                int type = qrand()%3 + 2;
                item* it = new item(x,y,this,type);
                items.append(it);
            }
        }
    }
}

void Widget::checkGetItem()
{
    if(myPlane->dead == 0){
        for (int i = 0; i < items.size(); i++) {
            item* it = items.at(i);
            if (it->item_label.geometry().intersects(myPlane->labelPlane.geometry())) {
                if(it->type == ITEM_DAMAGE || it->type == ITEM_ATTACK){
                    if(ifOpenSound){
                        Soundthread* thread = new Soundthread;
                        thread->play("qrc:/new/prefix1/res/get_bullet.wav");
                        Sounds.append(thread);
                    }
                }else if(it->type == ITEM_HEAL){
                    if(ifOpenSound){
                        Soundthread* thread = new Soundthread;
                        thread->play("qrc:/new/prefix1/res/heal.wav");
                        Sounds.append(thread);
                    }
                }

                items.removeOne(it);
                getItem(it->type);
                delete it;

                break;
            }
        }
    }
}

void Widget::getItem(int type)
{
    if(type == ITEM_DAMAGE){
        myPlane->getDamageBullet = true;

    }else if(type == ITEM_HEAL){
        int addHealth = myPlane->maxHealth * 0.25;
        int nextHealth = myPlane->health + addHealth;
        if(nextHealth > myPlane->maxHealth){
            nextHealth = myPlane->maxHealth;
        }
        myPlane->healthChange(myPlane->health, nextHealth);
        myPlane->health = nextHealth;

    }else if(type == ITEM_NUCLEAR){
        bool nohit = enemies.size() == 0;
        for(int i = 0;i <enemies.size();){
            Enemy* myenemy = enemies.at(i);
            //生成爆炸
            generateExplosion(myenemy->enemy.x(),myenemy->enemy.y());
            enemies.removeAt(i);
            delete myenemy;
        }
        if(!nohit){
            //播放音效
            Soundthread* thread = new Soundthread();Sounds.append(thread);

            if(ifOpenSound){
                thread->play(NORMAL_EXPLOSION_SOUND);
            }
        }
    }else if(type == ITEM_ATTACK){
        attackRate += 0.05;
    }
}

void Widget::moveExplosions()//移动的爆炸+爆炸动画
{
    // 遍历爆炸列表
    for (int i = 0; i < explosions.size(); ++i) {
        //qDebug()<<"end"<<i;
        Explosion* myexplosion = explosions.at(i);

        // 移动爆炸
        myexplosion->explode();
        if(myexplosion->explode_index == myexplosion->explode_map_num)
        {
            explosions.removeOne(myexplosion);
            myexplosion->explosion.deleteLater();
        }
    }
}

void Widget::moveBossExplosions()
{
    for (int i = 0; i < bossExplosions.size(); ++i) {
        Boss_explosion* myexplosion = bossExplosions.at(i);

        // 移动爆炸
        myexplosion->explode();
        if(myexplosion->explode_index == myexplosion->explode_map_num)
        {
            bossExplosions.removeOne(myexplosion);
            delete myexplosion;
        }
    }
}

void Widget::generateBullet()//生成子弹
{
    if(myPlane->dead == 0 && unstart == 0){
        myPlane->shoot(attackRate);
    }
}

void Widget::generateEnemyBullet() // 敌人子弹
{
    for(int i=0;i<enemies.size();i++){
        if(enemies[i]->enemyType == ENEMY_FLAME){
            Enemy* myenemy = enemies[i];
            makeEnemyBullet* mybullet = new makeEnemyBullet(myenemy->enemy.x(),
                                                            myenemy->enemy.y() + myenemy->enemy.height(),
                                                            50,
                                                            QPixmap(":/new/prefix1/ImgBox/enemySmallBullet.png").scaled(30,30,Qt::KeepAspectRatio),
                                                            4,
                                                            -90,this);

            // 将子弹添加到列表中
            enemyBullets.append(mybullet);
        }
        if(enemies[i]->enemyType == ENEMY_FLAME){
            Enemy* myenemy = enemies[i];
            makeEnemyBullet* mybullet = new makeEnemyBullet(myenemy->enemy.x() + myenemy->enemy.width() - 30,
                                                            myenemy->enemy.y() + myenemy->enemy.height(),
                                                            50,
                                                            QPixmap(":/new/prefix1/ImgBox/enemySmallBullet.png").scaled(30,30,Qt::KeepAspectRatio),
                                                            4,
                                                            -90,this);
            // 将子弹添加到列表中
            enemyBullets.append(mybullet);
        }
    }
}

void Widget::moveBullets()//移动子弹
{
    myPlane->moveBullets();
}

void Widget::moveEnemyBullets()//移动敌人子弹
{
    // 遍历子弹列表
    for (int i = 0; i < enemyBullets.size(); ++i) {
        makeEnemyBullet* mybullet = enemyBullets.at(i);
        // 移动子弹

        double x = mybullet->bullet.x();
        double y = mybullet->bullet.y();
        int speed = mybullet->speed;

        x += speed * qCos(qDegreesToRadians(mybullet->angle)); // x 方向移动距离
        y -= speed * qSin(qDegreesToRadians(mybullet->angle)); // y 方向移动距离
        //qDebug()<<speed<<x;
        mybullet->bullet.move(x, y);

        // 如果子弹超出屏幕范围，删除子弹
        if (mybullet->bullet.y() > WINDOW_H + 10) {
            enemyBullets.removeAt(i); // 从列表中移除子弹
            mybullet->bullet.deleteLater(); // 删除子弹对象
        }
    }
}

void Widget::generateEnemy()//生成敌机
{
    Enemy* myenemy = new Enemy(this, healthAddRate);
    // 将敌机添加到列表中
    enemies.append(myenemy);
}

void Widget::moveEnemies() //移动敌机
{
    // 遍历敌机列表
    for (int i = 0; i < enemies.size(); ++i) {
        Enemy* myenemy = enemies.at(i);
        // 移动敌机
        myenemy->enemy.move(myenemy->enemy.x(), myenemy->enemy.y() + myenemy->moveSpeed);

        // 如果敌机超出屏幕范围，删除敌机
        if (myenemy->enemy.y() > height()) {
            enemies.removeAt(i); // 从列表中移除敌机
            myenemy->enemy.deleteLater(); // 删除敌机对象
        }
    }
}

void Widget::moveItems() //移动道具
{
    // 遍历道具列表
    for (int i = 0; i < items.size(); ++i) {
        item* it = items.at(i);
        // 移动道具
        if(it->ifMove){
            it->item_label.move(it->item_label.x(), it->item_label.y()+5);
        }

        // 如果敌机超出屏幕范围，删除敌机
        if (it->item_label.y() > WINDOW_H) {
            items.removeAt(i); // 从列表中移除敌机
            delete it; // 删除敌机对象
        }
    }
}

void Widget::keyPressEvent(QKeyEvent* event) //键盘输入事件
{
    QString key = event->text();

    if(unstart == 0){
        // 检查当前输入是否满足触发条件
        if (key == "1" && userInput.isEmpty())
            userInput += key;

        else if (userInput == "1" && key == "1")
            userInput += key;
        else if (userInput == "11" && key == "4")
            userInput += key;
        else if (userInput == "114" && key == "5")
            userInput += key;
        else if (userInput == "1145" && key == "1")
            userInput += key;
        else if (userInput == "11451" && key == "4")
        {
  //          qDebug() << "用户输入了 114514 !";
            specicalRevival();//神奇的秘籍
            userInput.clear();
        }
        else
            userInput.clear();
    }

    // 手动发射子弹
    if(ifAutoShoot == 0 && unstart == 0 && myPlane->dead == 0){
        if(key == "z"){
            generateBullet();
        }
    }

    QWidget::keyPressEvent(event);

}

void Widget::mouseMoveEvent(QMouseEvent* event) //鼠标移动事件
{

    if (event->buttons() & Qt::LeftButton && (unstart == 0) && (myPlane->dead == 0) && (ifInPause == 0)) {//在start按下的条件下

        int x = event->x(),y = event->y();
        if(x <= 0) x = 0;
        if(x >= WINDOW_W) x = WINDOW_W;
        if(y <= 0 + fixedRange) y = 0 + fixedRange;
        if(y >= WINDOW_H) y = WINDOW_H;
        myPlane->moveTo(x-myPlane->labelPlane.width()/2,y-myPlane->labelPlane.height()/2);
    }

    QWidget::mouseMoveEvent(event);
}

void Widget::mousePressEvent(QMouseEvent* event) //鼠标按键事件    //包含大量信号和槽
{
    if (event->button() == Qt::LeftButton && unstart){//unstart控制是否点击了开始
        // 已改善
    }

    //测试用，输出相关信息
    if (event->button() == Qt::RightButton) {
                // 获取鼠标点击位置在窗口内的坐标
                QPoint pos = event->pos();

                //qDebug() << "Mouse Click Position: (" << pos.x() << ", " << pos.y() << ")";
               // qDebug() << calculateAngleBetweenPoints(myPlane->labelPlane.x() + myPlane->labelPlane.width()/2, myPlane->labelPlane.y(), pos.x(), pos.y());
            }
    QWidget::mousePressEvent(event);
}

void Widget::scrollBackground() //背景滚动
{
    scrollOffset += 0.8; //控制滚动速度

    // 如果滚动偏移量超过背景图片的高度，则将其重置为0，实现连续滚动的效果
    if (scrollOffset >= 0) {
        scrollOffset = -WINDOW_H;
    }

    update();
}

void Widget::paintEvent(QPaintEvent *) //绘制函数
{
    //绘制背景图片
    QPainter p(this);
    p.drawPixmap(0, scrollOffset, WINDOW_W, WINDOW_H*2, background_image);
}

int Widget::calculate_score(int enemy_health) //计算得分
{
    score += enemy_health/2;
    return score;
}

void Widget::failDoubleClick()  //没双击(现在暂时没用
{
    isDoubleClick = false;
    doubleClickTimer->stop();
}

void Widget::specicalRevival()
{
    if(myPlane->dead == 1){
        myPlane->dead = 0;
        myPlane->moveTo(WINDOW_W/2 - myPlane->labelPlane.width()/2, 779);
        myPlane->labelPlane.show();
        myPlane->health = myPlane->maxHealth;
        bulletGeneratorTimer->start();
        myPlane->healthChange(0, myPlane->maxHealth);
        if(ifOpenHealthBar)
        {
            myPlane->healthBar.show();
        }

        mainMusicThread2->effect.setVolume(1);
        mainMusicThread2->play(music[setting->mapIndex()]);
    }
}



void Widget::levelMode() //关卡选择函数
{
    presentTime = 0;
    connect(timeClick, &QTimer::timeout,
            [=](){
                presentTime++;

//                qDebug() << healthAddRate;
                if(presentTime%10 == 0){
                    healthAddRate += 0.01;
                }


                if(score >= BOSS2_SHOWUP_SCORE && boss2Out == 0){
                    generateBossType_2();
                    boss2Out = 1;
                    enemyGeneratorTimer->start(1200);
                }
                if(boss2Out && checkBoss2Death == 0){
                    if(nowBoss2->isDead){
                        enemyGeneratorTimer->start(600);
                        checkBoss2Death = 1;
                        healthAddRate *= 2;
                        if(myPlane->type == PLANE_SMALL){
                            attackRate +=0.5;
                        }
                    }
                }

                if(boss2Out && checkBoss2Death && score >= BOSS1_SHOWUP_SCORE && boss1Out == 0){
                    generateBossType_1();
                    boss1Out = 1;
                    enemyGeneratorTimer->stop();
                    presentTimers.removeOne(enemyGeneratorTimer);


                }
                if(boss1Out && checkBoss1Death == 0){
                    if(nowBoss1->isDead){
                        enemyGeneratorTimer->start(400);
                        presentTimers.append(enemyGeneratorTimer);
                        checkBoss1Death = 1;
                        healthAddRate += 2 * (double(myPlane->type)*0.5 + 0.5);
                        attackRate += 0.3;
                    }
                }

                 }
            );
}

void Widget::generateBossType_1() // 做一个BOSS，两个炮向玩家发射子弹，可以摧毁BOSS的两门炮，摧毁后BOSS防御降低
{

    fixedRange = 500;
    if(ifOpenSound){
        mainMusicThread2->setVolume(0);
        bossMusicThread->setVolume(1);
        bossMusicThread->play("qrc:/new/prefix1/res/boss_1.wav");
    }

    Boss1* myenemy = new Boss1(this);
    nowBoss1 = myenemy;
    myenemy->nowPlaneType = myPlane->type;
    myenemy->show();
    myenemy->setHealthRate(healthAddRate);
    myenemy->setDefenseRate(myPlane->type,attackRate);
    myenemy->HitCheck = new QTimer;
    myPlaneDeathCheck = new QTimer;
    lockTimer = new QTimer;
    connect(lockTimer,&QTimer::timeout,this,[=](){

        emit myenemy->lock(myPlane->labelPlane.x() + myPlane->labelPlane.width()/2,
                            myPlane->labelPlane.y(),&(this->enemyBullets));
    });
    lockTimer->start(250);
    presentTimers.append(lockTimer);

    //子弹击中BOSS
    connect(myenemy->HitCheck, &QTimer::timeout,this,&Widget::checkBulletHitBoss1);
    connect(myPlaneDeathCheck, QTimer::timeout, [=](){
        if(myPlane->dead == 1){
            lockTimer->stop();
            myPlaneDeathCheck->stop();
        }
    });
    myPlaneDeathCheck->start(10);
    presentTimers.append(myPlaneDeathCheck);
}

void Widget::generateBossType_2()
{
    fixedRange = 400;
    if(ifOpenSound){
        mainMusicThread2->setVolume(0);
        bossMusicThread->setVolume(1);
        bossMusicThread->play("qrc:/new/prefix1/res/boss_2.wav");
    }

    Boss2* boss = new Boss2(this);
    nowBoss2 = boss;
    boss->setHealthRate(healthAddRate);
    connect(boss->checkHit, &QTimer::timeout,this,&Widget::checkBulletHitBoss2);
    emit boss->begin(&(this->enemyBullets));
}

void Widget::checkBulletHitBoss1()
{
    if(!(nowBoss1->isDead)){
        QList<Bullet*> bulletsToDelete;//将要删除的列表
        // 遍历子弹列表
        for (int i = 0; i < myPlane->bullets.size(); i++) {
            Bullet* mybullet = myPlane->bullets.at(i);     //.at比[]更安全
            // 判断子弹和Gun是否重叠
            if (nowBoss1->bossLeftGun->gunHealth > 0 && mybullet->bullet.geometry().intersects(nowBoss1->bossLeftGun->GunLabel.geometry())) {
                bulletsToDelete.append(mybullet);
                //生成爆炸
                generateExplosion(mybullet->bullet.x() - 40, mybullet->bullet.y() - 40);
                //播放音效
                Soundthread* thread = new Soundthread();Sounds.append(thread);
                if(ifOpenSound){
                    thread->play(NORMAL_EXPLOSION_SOUND);
                }

                nowBoss1->gunGetHit(nowBoss1->bossLeftGun,mybullet->power);
                continue;
            }
            if (nowBoss1->bossRightGun->gunHealth > 0 && mybullet->bullet.geometry().intersects(nowBoss1->bossRightGun->GunLabel.geometry())) {
                bulletsToDelete.append(mybullet);
                //生成爆炸
                generateExplosion(mybullet->bullet.x() - 40, mybullet->bullet.y() - 40);
                //播放音效
                Soundthread* thread = new Soundthread();Sounds.append(thread);
                if(ifOpenSound){
                    thread->play(NORMAL_EXPLOSION_SOUND);
                }

                nowBoss1->gunGetHit(nowBoss1->bossRightGun,mybullet->power);
                continue;
            }
            if (mybullet->bullet.geometry().intersects(nowBoss1->bossLeftBody.geometry()) ||
                    mybullet->bullet.geometry().intersects(nowBoss1->bossRightBody.geometry())||
                    mybullet->bullet.geometry().intersects(nowBoss1->bossMiddleBody.geometry())) {// 击中身体部位
                bulletsToDelete.append(mybullet);
                if(nowBoss1->defLevel == 0){
                    //生成爆炸
                    generateExplosion(mybullet->bullet.x() - 45, mybullet->bullet.y() - 60);
                    //播放音效
                    Soundthread* thread = new Soundthread();Sounds.append(thread);
                    if(ifOpenSound){
                        thread->play(NORMAL_EXPLOSION_SOUND);
                    }
                }

                if(nowBoss1->defLevel == 0){
                    nowBoss1->addDamage += 100;// 炮台全无追伤，快速结束
                }

                int damage = mybullet->power - nowBoss1->def[nowBoss1->defLevel] + nowBoss1->addDamage;
                if(damage>0){
                    nowBoss1->bodyHealth -= damage;
                }

                nowBoss1->bossHealthBar.setValue(nowBoss1->bodyHealth);

                if(nowBoss1->bodyHealth <= 0){// BOSS被击败
                    mycounter->showNum(calculate_score(100000));
                    removeDeadBoss1(nowBoss1);
                    nowBoss1->isDead = true;
                    generateBossExplosion(10,10);
                    generateBossExplosion(250,100);
                    generateBossExplosion(450,150);
                    generateBossExplosion(10,10);
                    generateBossExplosion(250,100);
                    generateBossExplosion(450,150);
                    generateBossExplosion(10,10);
                }
            }
        }

        // 删除重叠的子弹
        for (Bullet* mybullet : bulletsToDelete) {
            myPlane->bullets.removeOne(mybullet);
            mybullet->bullet.deleteLater();
        }
    }
}

void Widget::checkBulletHitBoss2()
{
    QList<Bullet*> bulletsToDelete;//将要删除的列表
    // 遍历子弹列表
    for (int i = 0; i < myPlane->bullets.size(); i++) {
        Bullet* mybullet = myPlane->bullets.at(i);     //.at比[]更安全
            if (mybullet->bullet.geometry().intersects(nowBoss2->BossPlane.geometry()) ) {
                bulletsToDelete.append(mybullet);
                nowBoss2->health -= mybullet->power;
                //生成爆炸
                generateExplosion(mybullet->bullet.x() - 45, mybullet->bullet.y() - 60);
                //播放音效
                Soundthread* thread = new Soundthread();Sounds.append(thread);

                if(ifOpenSound){
                    thread->play(NORMAL_EXPLOSION_SOUND);
                }
            }
    }

    // 删除重叠的子弹
    for (Bullet* mybullet : bulletsToDelete) {
        myPlane->bullets.removeOne(mybullet);
        mybullet->bullet.deleteLater();
    }

    if(nowBoss2->health <= 0){// BOSS被击败
        nowBoss2->isDead = true;
        //nowBoss2 = nullptr;
        removeDeadBoss2(nowBoss2);
        generateBossExplosion(10,10);
        generateBossExplosion(250,100);
        generateBossExplosion(450,150);
        generateBossExplosion(10,10);
        generateBossExplosion(250,100);
        generateBossExplosion(450,150);
        generateBossExplosion(10,10);
        mycounter->showNum(calculate_score(20000));
        if(myPlane->dead == 0){
            generateItem(WINDOW_W/2, WINDOW_H/2, 200);
        }
    }
}

void Widget::removeDeadBoss1(Boss1* boss)
{
    // 检查并停止BOSS相关的定时器
    qDebug()<<"---------------";
    fixedRange = 0;
    if (lockTimer->isActive())
        lockTimer->stop();
    if (boss->HitCheck->isActive())
        boss->HitCheck->stop();
    if (myPlaneDeathCheck->isActive())
        myPlaneDeathCheck->stop();
    if (boss->movetimer->isActive())
        boss->movetimer->stop();
    presentTimers.removeOne(lockTimer);
    presentTimers.removeOne(boss->HitCheck);
    presentTimers.removeOne(myPlaneDeathCheck);
    presentTimers.removeOne(boss->movetimer);

    // 隐藏BOSS
    boss->hide();
    // 将BOSS从父窗口中移除（如果需要）
    boss->container.setParent(nullptr);

    if(ifOpenSound){
        bossMusicThread->setVolume(0);
        music_index = qrand()%4;
        mainMusicThread2->setVolume(1);
        mainMusicThread2->play(music[setting->mapIndex()]);
    }
//    nowBoss1 = nullptr;
}


void Widget::removeDeadBoss2(Boss2* boss)
{
    fixedRange = 0;
    // 检查并停止BOSS相关的定时器
    if (boss->movetimer->isActive())
        boss->movetimer->stop();
    if (boss->randomMove->isActive())
        boss->randomMove->stop();
    if (boss->checkHit->isActive())
        boss->checkHit->stop();
    if (boss->tickTimer->isActive())
        boss->tickTimer->stop();
    presentTimers.removeOne(boss->movetimer);
    presentTimers.removeOne(boss->randomMove);
    presentTimers.removeOne(boss->checkHit);
    presentTimers.removeOne(boss->tickTimer);


    if(ifOpenSound){
        bossMusicThread->setVolume(0);
        music_index = qrand()%4;
        mainMusicThread2->setVolume(1);
        mainMusicThread2->play(music[setting->mapIndex()]);
    }

    // 隐藏BOSS及其子元素
    boss->BossPlane.deleteLater();
}



Widget::~Widget()
{
    delete ui;
}
