#include "menu.h"
#include "view/ui_menu.h"
#include <QPushButton>

Menu::Menu(QWidget *parent,QString path)
    : Scene(parent,path)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(ui->startBtn,&QPushButton::clicked,this,&Menu::startBtnClicked);
}

Menu::~Menu()
{
    delete ui;
}
