#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMediaPlayer>
#include "soundthread.h"
#include <QKeyEvent>
#include "widget.h"
namespace Ui {
class Launcher;
}

class Launcher : public QWidget
{
    Q_OBJECT

public:
    explicit Launcher(QWidget *parent = 0);
    ~Launcher();
    void paintIcon(QMediaPlayer::State state);
    void keyPressEvent(QKeyEvent *event);

public:
    QLabel* label  = NULL;
    int iconAlpha = 255,step = 5;
    int x = 0,x2 = 0;
    int enex = 0,eney = 0;
    int h = 0;
    Soundthread* thread  = NULL;

    QTimer* iconTimer = NULL;

    Widget w;

signals:
    void widgetInit();

private:
    Ui::Launcher *ui;

};

#endif // LAUNCHER_H
