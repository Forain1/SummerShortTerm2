#include "cast.h"
#include "view/ui_cast.h"
#include "scene.h"
#include "role.h"
Cast::Cast(QWidget *parent,QString path)
    : Scene(parent,path)
    , ui(new Ui::Cast)
{
    ui->setupUi(this);
    for(int i = 0 ; i<roleCounts ; i++ ){
        Role* role = new Role(i,this);
        ui->roleLayout->addWidget(role);
        connect(role,&Role::roleBtnClicked,this,&Cast::roleBtnClicked);
    }
    connect(ui->fightBtn,&QPushButton::clicked,this,&Cast::fightBtnClicked);
    connect(ui->backBtn,&QPushButton::clicked,this,&Cast::backBtnClicked);

}

Cast::~Cast()
{
    delete ui;
}
