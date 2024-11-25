#include "explosion.h"
#include "config.h"
#include <QDebug>
Explosion::Explosion(QWidget* parent,int x ,int y)
{
    this->parent = parent;
    this->explosion.setParent(this->parent);
    this->explosion.setPixmap(QPixmap(explode_map[this->explode_index]));
    this->explosion.resize(explosion_size[this->explode_index]);
    this->explosion.move(x,y);
    this->explosion.show();
}

void Explosion::explode()
{
    // 移动爆炸
    this->explosion.move(this->explosion.x(), this->explosion.y() + 15);
    //切换图片，改变大小
    this->explode_index++;
    if(this->explode_index<4){
        this->explosion.setPixmap(this->explode_map[this->explode_index]);
        this->explosion.resize(this->explosion_size[this->explode_index]);

    }

}
