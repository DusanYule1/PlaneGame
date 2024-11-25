#include "config.h"
#include "enemy.h"

Enemy::Enemy(QWidget*parent, double healthAddRate)
{

    this->parent = parent;
    this->enemy.setParent(this->parent);
    this->enemyType = qrand() % 5 + 1;//随机种类
    this->moveSpeed = 3;//设置移动速度
    QPixmap enemyPixmap(enemyImagePaths[this->enemyType]);
    this->health = enemyHealth[this->enemyType] * healthAddRate;//血量设置
    this->enemy.setPixmap(enemyPixmap.scaled(enemy_size[this->enemyType], Qt::KeepAspectRatio));

    this->enemy.setGeometry(0,
                            0,
                            enemy_size[this->enemyType].width(),
                            enemy_size[this->enemyType].height());
    int x = qrand() % (WINDOW_W - this->enemy.geometry().width());

    setType();

    // 设置敌机初始位置
    this->enemy.move(x, -this->enemy.height()-50);
    this->enemy.lower();
    this->enemy.show();
}

void Enemy::setType()
{
    if(this->enemyType == ENEMY_TINY1 || this->enemyType == ENEMY_TINY2){
        this->moveSpeed = 5+qrand() % 2;//设置移动速度
    }else if(this->enemyType == ENEMY_HUGE){
        this->moveSpeed = 2;//设置移动速度
    }
    else if(this->enemyType == ENEMY_MIDDLE){
        this->moveSpeed = 3;
    }

}
