#ifndef ITEM_H
#define ITEM_H

#include "config.h"
#include <QPixmap>
#include <QLabel>
#include <QWidget>


class item
{
public:
    item(int x,int y,QWidget* parent = Q_NULLPTR,int type = 1);
    ~item();
public:
    QString item_pic[5] = {"",
                           ":/new/prefix1/res/item_damage.png",
                           ":/new/prefix1/res/item_heal.png",
                           ":/new/prefix1/res/item_nuclear.png",
                           ":/new/prefix1/res/item_attack.png"};
    QLabel item_label;
    int type = 1;

    bool ifMove = 1;


};

#endif // ITEM_H
