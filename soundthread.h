/***
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 *
 * .............................................
 *          佛祖保佑             永无BUG
 */


#ifndef SOUNDTHREAD_H
#define SOUNDTHREAD_H
#include <QObject>
#include <QSoundEffect>
class Soundthread : public QObject
{
    Q_OBJECT
public:
    explicit Soundthread(QObject* parent = Q_NULLPTR);
    ~Soundthread();

public:
    QSoundEffect effect;
//    bool OpenSound = 1;
public:
    void play(QString qrc);
    void setLoopCount(int loopCount = 0);
    void setVolume(double volume);
signals:

public slots:

private:

};

#endif // SOUNDTHREAD_H
