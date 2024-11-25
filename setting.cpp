#include "setting.h"
#include "ui_setting.h"
Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    about = new About();
    this->setFixedSize(WINDOW_W,WINDOW_H-100);
    this->setParent(parent);
    //设置里的内容
    labelSettingTitle.setParent(this);
    openHealthBar.setParent(this);
    openScoreBoard.setParent(this);
    openSound.setParent(this);
    changeModeButton.setParent(this);
    changeBackgrond.setParent(this);
    changeShootingMode.setParent(this);

//    设置setting图标
//    labelSettingTitle.setParent(parent);
    labelSettingTitle.setGeometry(WINDOW_W/2 - 100, 100,200,100);
    labelSettingTitle.setIcon(QIcon(QPixmap(":/new/prefix1/ImgBox/settingTitleWhight.png").scaled(200, 100, Qt::KeepAspectRatio)));
    labelSettingTitle.setWindowFlag(Qt::FramelessWindowHint);
    labelSettingTitle.setStyleSheet("QPushButton{border:0px}");
    labelSettingTitle.setIconSize(QSize(200,100));

    //设置里的内容
    initButton(&openHealthBar,200,100,WINDOW_W/3 - 100, WINDOW_H/4,"血量显示：开启","font-weight: bold;");
    initButton(&openScoreBoard,200,100,WINDOW_W/3*2 - 100, WINDOW_H/4,"计分板显示：开启","font-weight: bold;");
    initButton(&openSound,200,100,WINDOW_W/3 - 100, WINDOW_H/4*2,"声音：开启","font-weight: bold;");
    initButton(&changeModeButton,200,100,WINDOW_W/3*2 - 100, WINDOW_H/4*2,"当前模式：关卡","font-weight: bold;");
    initButton(&changeBackgrond,200,100,WINDOW_W/3 - 100, WINDOW_H/4*3,"切换背景:normal","font-weight: bold;");
    initButton(&changeShootingMode,200,100,WINDOW_W/3*2 - 100, WINDOW_H/4*3,"射击模式：自动","font-weight: bold;");

    connect(&openHealthBar, &QPushButton::clicked, this, &Setting::healthBarStatus);
    connect(&openScoreBoard, &QPushButton::clicked, this, &Setting::scoreBoardStatus);
    connect(&openSound, &QPushButton::clicked, this, &Setting::soundStatus);
    connect(&changeModeButton, &QPushButton::clicked, this, &Setting::modeChange);
    connect(&changeBackgrond, &QPushButton::clicked, this, &Setting::backgrondChange);
    connect(&changeShootingMode, &QPushButton::clicked, this, &Setting::shootingModeChange);
    connect(&labelSettingTitle,&QPushButton::clicked,this,[=](){about->show();});
}

Setting::~Setting()
{
    delete ui;
}

void Setting::initButton(QPushButton* button,int w,int h,int x,int y,QString title,QString stylesheet)
{
    button->setGeometry(x,y,w,h);
    button->setText(title);
    button->setStyleSheet(stylesheet);
}

void Setting::healthBarStatus()
{
    if(ifOpenHealthBar == 1){
        ifOpenHealthBar = 0;
        openHealthBar.setText("血量显示：关闭");
    }
    else{
        ifOpenHealthBar = 1;
        openHealthBar.setText("血量显示：开启");
    }
}

void Setting::scoreBoardStatus()
{
    if(ifOpenScoreBoard == 1){
        ifOpenScoreBoard = 0;
        openScoreBoard.setText("计分板显示：关闭");
    }
    else{
        ifOpenScoreBoard = 1;
        openScoreBoard.setText("计分板显示：开启");
    }
}

void Setting::soundStatus()
{
    if(ifOpenSound == 1){
        ifOpenSound = 0;
        openSound.setText("声音：关闭");
    }
    else{
        ifOpenSound = 1;
        openSound.setText("声音：开启");
    }
}

void Setting::modeChange()
{
    if(ifDebugMode == 1){
        ifDebugMode = 0;
        changeModeButton.setText("当前模式：关卡");
    }
    else{
        ifDebugMode = 1;
        changeModeButton.setText("当前模式：测试");
    }
}

void Setting::backgrondChange()
{
    map_index++;
    map_index = map_index%3;
    switch (map_index) {
    case 0:
        changeBackgrond.setText("切换背景：normal");
        break;
    case 1:
        changeBackgrond.setText("切换背景：hard");
        break;
    case 2:
        changeBackgrond.setText("切换背景：insane");
        break;
    default:
        break;
    }
    emit shiftMap(map_index);
}

void Setting::shootingModeChange()
{
    if(ifAutoShoot == 1){
        ifAutoShoot = 0;
        changeShootingMode.setText("射击模式：Z键");
    }
    else{
        ifAutoShoot = 1;
        changeShootingMode.setText("射击模式：自动");
    }
}

int Setting::mapIndex()
{
    return map_index;
}
