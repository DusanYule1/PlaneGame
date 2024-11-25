#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    ui->label_SL->setOpenExternalLinks(true);
    ui->label_SL->setText("<a style='color: green;' href=\"https://gitee.com/xu-zhengyu114514/group-assignment\">Gitee仓库");
}

About::~About()
{
    delete ui;
}
