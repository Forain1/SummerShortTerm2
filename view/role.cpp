#include "role.h"
#include "ui_role.h"

Role::Role(int num,QWidget *parent)
    : roleNum(num),QWidget(parent)
    , ui(new Ui::Role)
{
    ui->setupUi(this);
    connect(ui->roleBtn,&QPushButton::clicked,this,[this](){emit this->RoleBtnClicked(this->roleNum);});
}

Role::~Role()
{
    delete ui;
}
