#include "esc.h"
#include "ui_esc.h"

Esc::Esc(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Esc)
{
    ui->setupUi(this);
    ui->volume->setRange(0,100);
    connect(ui->pushButton,&QPushButton::clicked,this,&Esc::pressMenu);
    connect(ui->volume,&QSlider::valueChanged,this,&Esc::volumeChange);
}

Esc::~Esc()
{
    delete ui;
}
