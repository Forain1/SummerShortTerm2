#include "menu.h"
#include "view/ui_menu.h"
#include "about.h"
#include <QPushButton>

Menu::Menu(QWidget *parent,QString path)
    : Scene(parent,path)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(ui->startBtn,&QPushButton::clicked,this,&Menu::startBtnClicked);
    connect(ui->aboutBtn,&QPushButton::clicked,this,&Menu::showAbout);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::showAbout(){
    About about;
    about.exec();
}
