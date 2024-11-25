#ifndef BOSS_EXPLOSION_H
#define BOSS_EXPLOSION_H

#include "config.h"
#include "explosion.h"
#include <vector>
#define BOSS_EXPLOSION_WI 600
#define BOSS_EXPLOSION_HI 350

class Boss_explosion : public Explosion
{
public:
    Boss_explosion(QWidget* parent = Q_NULLPTR,int x = 0,int y = 0);

public:
    std::vector <QString> explode_map = { " ",
                                    ":/new/prefix1/res/explode_boss_1.png",
                                    ":/new/prefix1/res/explode_boss_2.png",
                                    ":/new/prefix1/res/explode_boss_3.png",
                                    ":/new/prefix1/res/explode_boss_4.png",
                                    ":/new/prefix1/res/explode_boss_5.png",
                                    ":/new/prefix1/res/explode_boss_6.png",
                                    ":/new/prefix1/res/explode_boss_7.png"
                                  };
public:
    void explode();
};

#endif // BOSS_EXPLOSION_H
