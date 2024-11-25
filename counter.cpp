#include "counter.h"
#include "config.h"
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QDebug>

counter::counter(QWidget* parent)
{
    for(int i = 0;i<NUMIMG_SIZE;i++){
        numImg[i].resize(QSize(NUMBER_W,NUMBER_H));
        numImg[i].move(0 + NUMBER_W*(i)+5,0);
        numImg[i].setParent(parent);

    }
}

void counter::showNum(int n)
{

    QString num = QString::number(n);
    int len = num.length();
    for(int i = 0;i<len;i++){
        int y = n%10;
        numImg[len - 1 - i].raise();
        numImg[len - 1 - i].setPixmap(QPixmap(":/new/prefix1/res/num" + QString::number(y) +".png").scaled(QSize(NUMBER_W,NUMBER_H),Qt::KeepAspectRatio));
        numImg[len - 1 - i].show();
        n/=10;
    }

}
