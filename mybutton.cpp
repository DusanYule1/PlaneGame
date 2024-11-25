#include "mybutton.h"
#include <QPixmap>
myButton::myButton(int w,int h,int x,int y,QString pic,QWidget *parent) : QPushButton(parent)
{
    this->setParent(parent);
    this-> setGeometry(x,y,w,h);
    this-> setIcon(QIcon(pic));
    this-> setWindowFlag(Qt::FramelessWindowHint);
    this-> setStyleSheet("QPushButton{border:0px}");
//    this->setAttribute(Qt::);
    this-> setIconSize(QSize(w,h));
//    this-> show();
}
