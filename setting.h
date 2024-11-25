#ifndef SETTING_H
#define SETTING_H

#include "config.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "about.h"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();
    void initButton(QPushButton* button,int w = 0 ,int h = 0,int x = 0,int y = 0,QString title = "",QString stylesheet = "");

    void healthBarStatus();
    void scoreBoardStatus();
    void soundStatus();
    void modeChange();
    void backgrondChange();
    void shootingModeChange();
    int mapIndex();

signals:
    void shiftMap(int map_index);

public:

    QPushButton labelSettingTitle;
    //设置界面的按钮
    QPushButton openHealthBar;
    QPushButton openScoreBoard;
    QPushButton openSound;
    QPushButton changeModeButton;
    QPushButton changeBackgrond;    //背景改变
    QPushButton changeShootingMode; //射击模式按钮
    bool ifOpenHealthBar = 1;
    bool ifOpenScoreBoard = 1;
    bool ifOpenSound = 1;
    bool ifDebugMode = 0;
    bool ifAutoShoot = 1;
    About* about = NULL;

private:
    Ui::Setting *ui;
    int map_index = 0;

//    friend class
};

#endif // SETTING_H
