#include "menu.h"
#include "view/ui_menu.h"

Menu::Menu(QWidget *parent,QString path)
    : Scene(parent,path)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}
