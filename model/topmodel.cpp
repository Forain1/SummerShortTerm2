#include "topmodel.h"
#include "../model/character.h"
#include "../model/scenestate.h"
#include "../model/characterstate.h"
#include "../common/index.h"

#include <QDebug>

TopModel::TopModel(QObject *parent)
    : QObject{parent}
    , c0(nullptr)
    , c1(nullptr)
{
    sceneState=new SceneState(this);
}

//在每次进入Battle页面时更新
void TopModel::initCharacter(){
    c0->setWidth(c0->getIdleWidth());
    c0->setHeight(c0->getIdleHeight());
    c1->setWidth(c1->getIdleWidth());
    c1->setHeight(c1->getIdleHeight());

    c0->setX(20);
    c0->setY(BATTLEHEIGHT-c0->getIdleHeight());
    c1->setX(BATTLEWIDTH-20-c1->getIdleWidth());
    c1->setY(BATTLEHEIGHT-c1->getIdleHeight());

    c0->setGroundY(BATTLEHEIGHT-c0->getIdleHeight());
    c1->setGroundY(BATTLEHEIGHT-c1->getIdleHeight());

    c0->setCurrentHealth(100);
    c1->setCurrentHealth(100);
}

//获取创建角色所需的相关信息
void TopModel::getInfo(int c0Width,int c0Height,int c1Width,int c1Height){
    if(c0!=nullptr)delete c0;
    if(c1!=nullptr)delete c1;
    c0 = new Character(Index::rightIndex,this);
    c1 = new Character(Index::leftIndex,this);

    c0->setIdleWidth(c0Width);
    c0->setIdleHeight(c0Height);
    c1->setIdleWidth(c1Width);
    c1->setIdleHeight(c1Height);
}

void TopModel::nextFrame(){
    // 检查角色是否已创建
    if(c0 == nullptr || c1 == nullptr) return;
    
    //各种model的交互
    judgeHurt();
    //调用各种model自身的nextFrame
    c0->nextFrame();
    c1->nextFrame();
    if(isGameOver()){
        emit gameOver();
    }
}

bool TopModel::isGameOver(){
    if(c0 == nullptr || c1 == nullptr) return false;
    return c0->getCurrentHealth()<=0||c1->getCurrentHealth()<=0;
}

bool TopModel::isCharacterOverlapping(){
    if(c0 == nullptr || c1 == nullptr) return false;
    int c0x0,c0x1,c0y0,c0y1,c1x0,c1x1,c1y0,c1y1;
    if(c0->getDirection()==Index::leftIndex){
        c0x0=c0->getX()-c0->getAttackWidth();
        c0x1=c0->getX()+c0->getWidth();
    }
    else{
        c0x0=c0->getX();
        c0x1=c0->getX()+c0->getWidth()+c0->getAttackWidth();
    }
    if(c1->getDirection()==Index::leftIndex){
        c1x0=c1->getX()-c1->getAttackWidth();
        c1x1=c1->getX()+c1->getWidth();
    }
    else{
        c1x0=c1->getX();
        c1x1=c1->getX()+c1->getWidth()+c1->getAttackWidth();
    }
    c0y0=c0->getY();
    c0y1=c0->getY()+c0->getHeight();
    c1y0=c1->getY();
    c1y1=c1->getY()+c1->getHeight();

    bool xOverlap = !(c0x1 < c1x0 || c1x1 < c0x0);
    bool yOverlap = !(c0y1 < c1y0 || c1y1 < c0y0);
    qDebug()<<"xOverlap:"<<xOverlap;
    qDebug()<<"yOverlap:"<<yOverlap;
    return xOverlap && yOverlap;
}

void TopModel::judgeHurt(){
    if(c0 == nullptr || c1 == nullptr) return;
    
    if(isCharacterOverlapping()){
        if(c1->getState()->getStateIndex()==Index::AttackingState && !c1->getHasHit()){
            if(c0->getState()->getStateIndex()==Index::DefendingState)
                c0->setCurrentHealth(c0->getCurrentHealth()-2);
            else
                c0->setCurrentHealth(c0->getCurrentHealth()-5);
            c1->setHasHit(true);
        }
        if(c0->getState()->getStateIndex()==Index::AttackingState && !c0->getHasHit()){
            if(c1->getState()->getStateIndex()==Index::DefendingState)
                c1->setCurrentHealth(c1->getCurrentHealth()-2);
            else
                c1->setCurrentHealth(c1->getCurrentHealth()-5);
            c0->setHasHit(true);
        }
    }
}
