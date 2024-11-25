#include "form.h"
#include "ui_form.h"
#include <QThread>
#include <QHostInfo>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    socket = new QUdpSocket;
    soc = new QUdpSocket;
    thread = new QThread();
    thread->start();
    QHostAddress add;
    add.setAddress("0.0.0.0");
    soc->bind(1145);//send
    soc->moveToThread(thread);
    socket->moveToThread(thread);
    socket->bind(add,1145);//receive
    connect(socket,&QUdpSocket::readyRead,this,&Form::showText);
    connect(ui->pushButton,&QPushButton::clicked,this,&Form::sendText);

    QString localHostName = QHostInfo::localHostName();
        qDebug() << "localHostName" << localHostName;

        //获取本机的IP地址(可能有多条）
        QHostInfo info = QHostInfo::fromName(localHostName);
        qDebug()<<"IP Address："<< info.addresses();

        //只输出IPv4地址（可能有多条）
        foreach(QHostAddress address,info.addresses())
        {
            if(address.protocol() == QAbstractSocket::IPv4Protocol){

                qDebug() <<"My localhost IPv4 address: "<< address.toString();
                QString a =  address.toString();
                b = "";
                int t = 0;
                for(int i = 0 ; i < a.length() && t < 2;i ++){
                    if(a[i] == '.'){
                        t++;
                    }
                    b+=a[i];
                }
                qDebug()<<b;
                break;
            }
        }
}

Form::~Form()
{
    delete ui;
}

void Form::sendText()
{
    QString s = ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText(s);
    ui->lineEdit->clear();
    QString to = ui->sendTo->text();
    if(to.isEmpty()){
        for(int i = 1 ; i < 255;i++){
            for(int j = 1 ; j < 255;j++){
                QString addr = b;
                addr += QString::number(i);
                addr+=".";
                addr+=QString::number(j);
                qDebug()<<addr;
                qDebug()<<i<<soc->writeDatagram(s.toUtf8(),QHostAddress(addr),1145);
            }
        }

    }
        else{
        QHostAddress ip(to);
        soc->writeDatagram(s.toUtf8(),ip,1145);
    }
}

void Form::showText()
{
    while(socket->hasPendingDatagrams())  // 判断是否有待读取的数据
       {
           QByteArray datagram;
           datagram.resize(socket->pendingDatagramSize()); // 获取待读取数据报的字节数

           QHostAddress peerAddr;
           quint16 peerPort;
           socket->readDatagram(datagram.data(),datagram.size(),&peerAddr,&peerPort); // 读取数据报内容
           QString str=datagram.data();

           QString peer="[From "+peerAddr.toString() + "] ";

           //qDebug()<<peer+str;
           ui->plainTextEdit->appendPlainText(peer + str);
       }
}
