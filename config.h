#ifndef CONFIG_H
#define CONFIG_H

#define WINDOW_W 800
#define WINDOW_H 1200

#define ICON_W 750
#define ICON_H 900

#define BULLET_TYPE 4//子弹种类数量

#define BOSS1_SHOWUP_SCORE 25000
#define BOSS2_SHOWUP_SCORE 8000

#define ITEM_WI 50
#define ITEM_HI 50
#define ITEM_DAMAGE 1
#define ITEM_HEAL 2
#define ITEM_NUCLEAR 3
#define ITEM_ATTACK 4

#define SPEED 5

#define HERO_PLANE_W 200
#define HERO_PLANE_H (64*2)
#define HERO_PLANE_1_W 200
#define HERO_PLANE_1_H 128
#define HERO_PLANE_2_W 178
#define HERO_PLANE_2_H 133
#define HERO_PLANE_3_W 300
#define HERO_PLANE_3_H 200


#define ENEMY_GENERATE_INTERVAL 600

#define BULLET_NUM 30
#define BULLET_1_W 50
#define BULLET_1_H 50
#define BULLET_2_W 25
#define BULLET_2_H 80
#define BULLET_3_W 50
#define BULLET_3_H 115
#define BULLET_4_W 20
#define BULLET_4_H 82

#define ENEMY_NUM 15
#define ENEMY_1_W 120
#define ENEMY_1_H 84
#define ENEMY_2_W 200
#define ENEMY_2_H 150
#define ENEMY_3_W 100
#define ENEMY_3_H 70
#define ENEMY_4_W 100
#define ENEMY_4_H 70
#define ENEMY_5_W 150
#define ENEMY_5_H 93

#define EXPLODE_1_W 64
#define EXPLODE_2_W 128
#define EXPLODE_3_W 128
#define EXPLODE_NUM BULLET_NUM*2
#define EXPLODE_BOSS_1_W 128
#define EXPLODE_BOSS_2_W 64

#define BOSS_WT 800
#define BOSS_HT 382
#define BOSS_HEALTH 1000

#define SHOOT_SOUND_1 "qrc:/new/prefix1/res/attack_1.wav"
#define NORMAL_EXPLOSION_SOUND "qrc:/new/prefix1/res/explode_1.wav"
#define ENEMY_EXPLODE_SOUND_1 "qrc:/new/prefix1/res/explode_2.wav"

#define PLANE_1_W 150
#define PLANE_1_H 104
#define PLANE_2_W 200
#define PLANE_2_H 150
#define PLANE_3_W 240
#define PLANE_3_H 156

//计数器单个数字尺寸
#define NUMBER_W 75
#define NUMBER_H NUMBER_W


#endif // CONFIG_H
