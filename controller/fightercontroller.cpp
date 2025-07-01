#include "fightercontroller.h"
#include "../common/index.h"
#include<QEvent>
#include<QKeyEvent>
FighterController::FighterController(Battle* battle,QObject *parent)
    : QObject{parent},battle(battle)
{
    battle->installEventFilter(this);

    //新建两个model绑定对应的view
    c0 = new Character(20,BATTLEHEIGHT-battle->getHeight(0),this);
    c1 = new Character(BATTLEWIDTH-20-battle->getWidth(1),BATTLEHEIGHT-battle->getHeight(1),this);

    //计时器逻辑
    timer=new QTimer(this);
    timer->setInterval(100);
    //通知model更新
    connect(timer,&QTimer::timeout,c0,&Character::nextFrame);
    connect(timer,&QTimer::timeout,c1,&Character::nextFrame);
    //model更新完毕，更新view
    connect(c0,&Character::frameUpdate,battle->fighter0,&Fighter::nextFrame);
    connect(c1,&Character::frameUpdate,battle->fighter1,&Fighter::nextFrame);
    timer->start();
    //
    qDebug() << "View size:" << battle->size();
    qDebug() << "Viewport size:" <<  battle->viewport()->size();
    qDebug() << "Scene rect:" <<  battle->sceneRect();
    qDebug() << "Visible scene area:" <<  battle->mapToScene( battle->viewport()->rect()).boundingRect();
}

bool FighterController::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_A:
            pressKeyA();
            break;
        case Qt::Key_D:
            pressKeyD();
            break;
        case Qt::Key_S:
            pressKeyS();
            break;
        case Qt::Key_W:
            pressKeyW();
            break;
        case Qt::Key_Left:
            pressKeyLeft();
            break;
        case Qt::Key_Right:
            pressKeyRight();
            break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_A:

        case Qt::Key_D:
            c0->setXSpeed(0);
            break;
        case Qt::Key_Left:
        case Qt::Key_Right:
            c1->setXSpeed(0);
            break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}


void FighterController::pressKeyA(){
    if(true){//需要在这里检测碰撞
        c0->switchToWalkingState(-10);
    }
}

void FighterController::pressKeyD(){
    if(true){//需要检测碰撞
        c0->switchToWalkingState(10);
    }
}

void FighterController::pressKeyW(){
    c0->switchToJumpingState();
}

void FighterController::pressKeyS(){
    c0->switchToDefendingState();
}

void FighterController::pressKeyLeft(){
    if(true){
        c1->switchToWalkingState(-10);
    }
}

void FighterController::pressKeyRight(){
    if(true){
        c1->switchToWalkingState(10);
    }
}

void FighterController::pressKeyUp(){
    c1->switchToJumpingState();
}

void FighterController::pressKeyDown(){
    c1->switchToDefendingState();
}
