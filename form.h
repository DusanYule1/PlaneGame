#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    void sendText();
    ~Form();


public:
    QUdpSocket* socket = NULL;
    QUdpSocket* soc = NULL;
    QString b;
    QThread* thread = NULL;

private:
    Ui::Form *ui;

public slots:
    void showText();
};

#endif // FORM_H
