#ifndef COUNTER_H
#define COUNTER_H
#define NUMIMG_SIZE 10
#include "config.h"
#include <QWidget>
#include <QImage>
#include <QLabel>
class counter
{
public:
    counter(QWidget* parent);
    void showNum(int n);

public:

    QLabel numImg[NUMIMG_SIZE];
};

#endif // COUNTER_H
