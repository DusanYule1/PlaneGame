#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class myButton : public QPushButton
{
public:
    myButton(int w,int h,int x,int y,QString pic,QWidget *parent = Q_NULLPTR);


};

#endif // MYBUTTON_H
