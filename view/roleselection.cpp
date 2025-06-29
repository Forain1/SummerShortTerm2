#include "roleselection.h"
#include "ui_roleselection.h"

RoleSelection::RoleSelection(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RoleSelection)
{
    ui->setupUi(this);
}

RoleSelection::~RoleSelection()
{
    delete ui;
}
