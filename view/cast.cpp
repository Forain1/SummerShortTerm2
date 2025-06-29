#include "cast.h"
#include "view/ui_cast.h"
#include "scene.h"
#include "roleselection.h"
Cast::Cast(QWidget *parent,QString path)
    : Scene(parent,path)
    , ui(new Ui::Cast)
{
    ui->setupUi(this);
    ui->roleLayout->addWidget(new RoleSelection(this));
}

Cast::~Cast()
{
    delete ui;
}
