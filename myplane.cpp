#include "widget.h"
#include "config.h"
#include "bullet.h"
#include "soundthread.h"
#include "myplane.h"
#include <qmath.h>

MyPlane::MyPlane(QWidget* parent)
{
    this->parent = parent;
    labelPlane.setParent(this->parent);
    healthBar.setParent(this->parent);
    valueChangeAnimation = new QPropertyAnimation(&healthBar, "value", this->parent);
    valueChangeAnimation->setDuration(500); // 数值改变动画持续1秒
    //血量槽设置
    healthBar.setStyleSheet("QProgressBar { border: 1px solid gray; border-radius: 5px; background: white; }"
                             "QProgressBar::chunk { background: red; }");
    healthBar.setOrientation(Qt::Horizontal); // 设置为水平方向
    healthBar.resize(150, 10); // 设置血量槽大小
    healthBar.setFormat(""); // 设置显示格式为空字符串
}

void MyPlane::setMaxHealthIndex(int MaxHealthIndex)
{
    maxHealth = planeHealth[MaxHealthIndex];//本机血量设置
}

void MyPlane::setHealth(int health)
{
    this->health = health;
}
bool MyPlane::shoot(double attackRate)//生成子弹
{
    int b_type = this->type;
    if(b_type == BULLET_MIDDLE){
        if(!getDamageBullet){
            generateBullet(labelPlane.x() + labelPlane.width() / 2,
                           labelPlane.y() - 10,
                           b_type,attackRate);
        }
        else{
            generateBullet(labelPlane.x() + labelPlane.width() / 2 - 20,
                           labelPlane.y() - 10,
                           b_type,attackRate);
            generateBullet(labelPlane.x() + labelPlane.width() / 2 + 20,
                           labelPlane.y() - 10,
                           b_type,attackRate);
        }

        return true;

    }else{
        if(b_type == BULLET_STRONG){
            static int limitRate = 2;
            if(getDamageBullet && limitRate == 2){
                limitRate = 1;
            }

            if(--cannon_interval == 0){
                cannon_interval = limitRate;
                generateBullet(labelPlane.x() + labelPlane.width() / 2,
                               labelPlane.y() - 10,
                               b_type,attackRate);
                return true;
            }
            else return false;

        }else if(b_type == BULLET_TINY){
            if(!getDamageBullet){
                generateBullet(labelPlane.x() + labelPlane.width() / 2,
                               labelPlane.y() - 10,
                               b_type,attackRate);
            }else{
                generateBullet(labelPlane.x() + labelPlane.width() / 2,
                               labelPlane.y() - 10,
                               BULLET_DAMAGE,attackRate);
            }
            return true;

        }

    }

}

void MyPlane::generateBullet(int x,int y,int b_type,double attackRate)
{
    Bullet* mybullet = new Bullet(this->parent,x,y,b_type,attackRate);
//    mybullet->bullet.setStyleSheet("border: 1px solid black;");
    if(b_type == BULLET_DAMAGE){
        mybullet->couldGoThroughEnemy = 1;
    }
    // 将子弹添加到列表中
    bullets.append(mybullet);
}

void MyPlane::moveBullets()//移动子弹
{
    // 遍历子弹列表
    for (int i = 0; i < bullets.size(); ++i) {
        Bullet* mybullet = bullets.at(i);
        // 移动子弹

        double x = mybullet->bullet.x();
        double y = mybullet->bullet.y();
        int speed = 5;
        x += speed * qCos(qDegreesToRadians(mybullet->angle)); // x 方向移动距离
        y -= speed * qSin(qDegreesToRadians(mybullet->angle)); // y 方向移动距离

        mybullet->bullet.move(x, y);

        // 如果子弹超出屏幕范围，删除子弹
        if (mybullet->bullet.y() < -mybullet->bullet.height()) {
            bullets.removeAt(i); // 从列表中移除子弹
            mybullet->bullet.deleteLater(); // 删除子弹对象
        }
    }
}

void MyPlane::healthChange(int startValue, int endValue) // 血条消失动画
{
    if (valueChangeAnimation->state() == QAbstractAnimation::Running) {
        valueChangeAnimation->stop();
    }

//    progressBar->setValue(endValue);
    valueChangeAnimation->setStartValue(startValue);
    valueChangeAnimation->setEndValue(endValue);
    valueChangeAnimation->start();
}

void MyPlane::setType(int type)
{
    this->type = type;
    this->labelPlane.setPixmap(QPixmap(planePic[this->type]).scaled(planeSize[this->type], Qt::KeepAspectRatio));
    this->labelPlane.resize(planeSize[this->type]);
    //qDebug()<<this->labelPlane.width()<<this->labelPlane.height();
}

void MyPlane::moveTo(int x,int y)
{
    this->labelPlane.move(x, y);
    this->healthBar.move(this->labelPlane.x() + this->labelPlane.width()/2 - this->healthBar.width()/2,
                         this->labelPlane.y() + this->labelPlane.height() + 5); // 设置血量槽位置

}

void MyPlane::moveTo(QPoint p)
{
    this->labelPlane.move(p);
    this->healthBar.move(this->labelPlane.x() + this->labelPlane.width()/2 - this->healthBar.width()/2,
                         this->labelPlane.y() + this->labelPlane.height() + 5); // 设置血量槽位置

}
