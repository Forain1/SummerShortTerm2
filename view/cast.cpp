#include "cast.h"
#include "view/ui_cast.h"
#include "scene.h"
Cast::Cast(QWidget *parent,QString path)
    : Scene(parent,path)
    , ui(new Ui::Cast)
{
    ui->setupUi(this);
}

Cast::~Cast()
{
    delete ui;
}
