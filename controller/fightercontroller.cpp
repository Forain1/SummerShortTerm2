#include "fightercontroller.h"
#include<QEvent>
#include<QKeyEvent>
FighterController::FighterController(Battle* battle,QObject *parent)
    : QObject{parent},battle(battle)
{
    battle->installEventFilter(this);

    //新建两个model绑定对应的view
    c0 = new Character(20,900-battle->getHeight(0),this);
    c1 = new Character(1600-20-battle->getWidth(1),900-battle->getHeight(1),this);

    //计时器逻辑
    timer=new QTimer(this);
    timer->setInterval(100);
    //通知model更新状态和帧数
    connect(timer,&QTimer::timeout,c0,&Character::nextFrame);
    connect(timer,&QTimer::timeout,c1,&Character::nextFrame);
    //model状态和帧数更新完毕，view更新状态和帧数
    connect(c0,&Character::frameUpdate,battle->fighter0,&Fighter::nextFrame);
    connect(c1,&Character::frameUpdate,battle->fighter1,&Fighter::nextFrame);

    //model坐标更新完毕，view更新坐标
    connect(c0,&Character::CoordinateUpdate,this,[=](int x,int y){battle->setCoodinate(0,x,y);});
    connect(c1,&Character::CoordinateUpdate,this,[=](int x,int y){battle->setCoodinate(1,x,y);});

    timer->start();
}

bool FighterController::eventFilter(QObject* obj,QEvent* event){
    if(event->type()==QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_A:
            pressKeyA();
            break;
        case Qt::Key_D:
            pressKeyD();
            break;
        default:
            return QObject::eventFilter(obj,event);
        }
        return true;
    }else{
       return QObject::eventFilter(obj,event);
    }
}

void FighterController::pressKeyA(){
    if(true){//需要在这里检测碰撞
        c0->setCoordinate(-10,0);
    }
}

void FighterController::pressKeyD(){
    if(true){//需要检测碰撞
        c0->setCoordinate(10,0);
    }
}
