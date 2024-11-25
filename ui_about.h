/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_SL;

    void setupUi(QWidget *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(477, 375);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(About);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(21);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(About);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(15);
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(About);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setPointSize(11);
        label_3->setFont(font2);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(About);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font2);

        verticalLayout->addWidget(label_4);

        label_SL = new QLabel(About);
        label_SL->setObjectName(QStringLiteral("label_SL"));
        label_SL->setFont(font2);

        verticalLayout->addWidget(label_SL);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QWidget *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About", Q_NULLPTR));
        label->setText(QApplication::translate("About", "<html><head/><body><p align=\"center\">\345\205\263\344\272\216</p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("About", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">\344\275\234\350\200\205\357\274\232</span>\350\247\243\346\210\220\346\230\261\343\200\201\345\276\220\345\276\201\345\256\207</p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("About", "<html><head/><body><p align=\"center\"><span style=\" font-style:italic;\">\347\211\271\345\210\253\351\270\243\350\260\242\357\274\232\351\237\251\345\245\207\345\261\225</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("About", "\347\211\210\346\234\254\345\217\267\357\274\232Ver1.0.0", Q_NULLPTR));
        label_SL->setText(QApplication::translate("About", "Gitee\344\273\223\345\272\223", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
