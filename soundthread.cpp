#include "soundthread.h"
#include "config.h"
#include <QSoundEffect>
#include <QThread>
#include <QSound>
#include <QDebug>
#include <QObject>
Soundthread::Soundthread(QObject* parent) : QObject(parent)
{
    effect.setVolume(0.3);
}

Soundthread::~Soundthread()
{

}

void Soundthread::play(QString audio)
{
    effect.setSource(QUrl(audio));
    effect.play();
}

void Soundthread::setVolume(double volume)
{
    effect.setVolume(volume);
}

void Soundthread::setLoopCount(int loopCount)
{
    effect.setLoopCount(loopCount);
}

