#include "boss_explosion.h"

Boss_explosion::Boss_explosion(QWidget* parent,int x,int y) : Explosion(parent,x,y)
{
    this->parent = parent;
    this->explosion.setParent(this->parent);
    this->explosion.setPixmap(QPixmap(explode_map[this->explode_index]));
    this->explosion.resize(QSize(BOSS_EXPLOSION_WI,BOSS_EXPLOSION_HI));
    this->explosion.move(x,y);
    this->explosion.show();
    this->explode_map_num = 7;
    this->type = 1;
}

void Boss_explosion::explode()
{
    // 移动爆炸
   // this->explosion.move(this->explosion.x(), this->explosion.y() + 15);
    //切换图片，改变大小
    this->explode_index++;
    if(this->explode_index < this->explode_map.size()){
        this->explosion.setPixmap(this->explode_map[this->explode_index]);
    }
}
