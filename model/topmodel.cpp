#include "topmodel.h"
#include "../model/character.h"
#include "../model/scenestate.h"
#include "../model/characterstate.h"
#include "../common/index.h"

TopModel::TopModel(QObject *parent)
    : QObject{parent}
{
    sceneState=new SceneState(this);
    c0 = new Character(Index::rightIndex,this);
    c1 = new Character(Index::leftIndex,this);
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

//在roleSelection时获取相关信息
void TopModel::getSize(int c0Width,int c0Height,int c1Width,int c1Height){
    c0->setIdleWidth(c0Width);
    c0->setIdleHeight(c0Height);
    c1->setIdleWidth(c1Width);
    c1->setIdleHeight(c1Height);
}

void TopModel::nextFrame(){
    //各种model的交互
    judgeHurt();
    if(!isGameOver()){
        //调用各种model自身的nextFrame
        c0->nextFrame();
        c1->nextFrame();
    }
}

bool TopModel::isGameOver(){
    return c0->getCurrentHealth()<=0||c1->getCurrentHealth()<=0;
}

bool TopModel::isCharacterOverlapping(){
    return !(c0->getX()+c0->getWidth()<=c1->getX()||
             c1->getX()+c1->getWidth()<=c0->getX()||
             c0->getY()+c0->getHeight()<=c1->getY()||
             c1->getY()+c1->getHeight()<=c0->getY());
}

void TopModel::judgeHurt(){
    if(isCharacterOverlapping()){
        if(c1->getState()->getStateIndex()==Index::AttackingState){
            if(c0->getState()->getStateIndex()==Index::DefendingState) c0->setCurrentHealth(c0->getCurrentHealth()-2);
            else c0->setCurrentHealth(c0->getCurrentHealth()-5);
        }
        if(c0->getState()->getStateIndex()==Index::AttackingState){
            if(c1->getState()->getStateIndex()==Index::DefendingState) c1->setCurrentHealth(c1->getCurrentHealth()-2);
            else c1->setCurrentHealth(c1->getCurrentHealth()-5);
        }
    }
}
