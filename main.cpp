#include "widget.h"
#include "launcher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
    Launcher l;
    l.show();
//    w.show();

    return a.exec();
}
