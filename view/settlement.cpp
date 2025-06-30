#include "settlement.h"
#include "view/ui_settlement.h"
#include <QPushButton>

Settlement::Settlement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settlement)
{
    ui->setupUi(this);
    connect(ui->onceMoreBtn,&QPushButton::clicked,this,&Settlement::onceMoreBtnClicked);
    connect(ui->returnMenuBtn,&QPushButton::clicked,this,&Settlement::returnMenuBtnClicked);
}

Settlement::~Settlement()
{
    delete ui;
}
