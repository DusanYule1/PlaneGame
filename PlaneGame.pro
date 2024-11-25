#-------------------------------------------------
#
# Project created by QtCreator 2023-07-27T21:20:10
#
#-------------------------------------------------

QT       += core gui multimedia websockets network multimediawidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlaneGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    counter.cpp \
    soundthread.cpp \
    bullet.cpp \
    emeny.cpp \
    myplane.cpp \
    explosion.cpp \
    boss1.cpp \
    item.cpp \
    form.cpp \
    mybutton.cpp \
    launcher.cpp \
    boss2.cpp \
    setting.cpp \
    boss_explosion.cpp \
    about.cpp \
    makeenemybullet.cpp \
    bossgun.cpp

HEADERS += \
        widget.h \
    counter.h \
    soundthread.h \
    makeenemybullet.h \
    bullet.h \
    config.h \
    enemy.h \
    myplane.h \
    explosion.h \
    boss1.h \
    item.h \
    form.h \
    mybutton.h \
    launcher.h \
    boss2.h \
    setting.h \
    boss_explosion.h \
    about.h \
    bossgun.h

FORMS += \
        widget.ui \
    form.ui \
    launcher.ui \
    setting.ui \
    about.ui

RESOURCES += \
    imgs.qrc \

CONFIG += resources_big
