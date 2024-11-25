#include "item.h"


item::item(int x,int y,QWidget* parent,int type)
{
    this->item_label.setParent(parent);
    this->type = type;
    this->item_label.setFixedSize(ITEM_WI,ITEM_HI);

    this->item_label.move(x,y);
    this->item_label.setPixmap(QPixmap(item_pic[this->type]).scaled(ITEM_WI,ITEM_HI,Qt::KeepAspectRatio));

    this->item_label.show();


}

item::~item()
{
    this->item_label.deleteLater();
}
