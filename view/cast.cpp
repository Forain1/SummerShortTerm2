#include "cast.h"
#include "view/ui_cast.h"
#include "scene.h"
#include "role.h"
Cast::Cast(QWidget *parent,QString path)
    : Scene(parent,path)
    , ui(new Ui::Cast)
{
    ui->setupUi(this);
    //添加可选角色按钮
    for(int i = 0 ; i<roleCounts ; i++ ){
        Role* role = new Role(i,this);
        ui->roleLayout->addWidget(role);
        connect(role,&Role::roleBtnClicked,this,&Cast::checkValid);
        connect(role,&Role::roleBtnClicked,this,&Cast::roleBtnClicked);
        connect(this,&Cast::setRoleBtn,role,&Role::setBtn);
    }
    //连接进入战斗按钮和回退按钮
    connect(ui->fightBtn,&QPushButton::clicked,this,&Cast::fightBtnClicked);
    connect(ui->backBtn,&QPushButton::clicked,this,&Cast::backBtnClicked);

    //将战斗按钮和回退按钮的信号绑定到Reset函数
    connect(ui->fightBtn,&QPushButton::clicked,this,&Cast::reset);
    connect(ui->backBtn,&QPushButton::clicked,this,&Cast::reset);

    //对角色选择进行判断,如果此时两个玩家都确认了选择的角色,才可以进入战斗
    ui->fightBtn->setEnabled(false);
}

Cast::~Cast()
{
    delete ui;
}

void Cast::checkValid(int roleNum){
    if(roleChooseCount++==0){
        ui->playerChooseLabel->setText("请玩家2选择你的角色");
        qDebug()<<"玩家1选择"<<roleNum;
    }else{
        ui->playerChooseLabel->setText("请点击Fight按钮开始游戏");
        qDebug()<<"玩家2选择"<<roleNum;
        roleChooseCount=0;
        ui->fightBtn->setEnabled(true);
        emit setRoleBtn(false);
    }
}

void Cast::reset(){
    ui->playerChooseLabel->setText("请玩家1选择你的角色");
    roleChooseCount = 0;
    ui->fightBtn->setEnabled(false);
    emit setRoleBtn(true);
}
