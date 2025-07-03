#include "esc.h"
#include "ui_esc.h"

Esc::Esc(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Esc)
{
    ui->setupUi(this);
}

Esc::~Esc()
{
    delete ui;
}
