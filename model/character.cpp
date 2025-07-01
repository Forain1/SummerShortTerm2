#include "character.h"
#include "characterstate.h"
#include <QDebug>
Character::Character(int x,int y,QObject *parent)
    : QObject{parent},maxHealth{100},currentHealth{100},x(x),y(y)
{
   state=new IdleState(this);

}

void Character::nextFrame(){
    qDebug()<<"xspeed:"<<xSpeed<<"state"<<state->getStateIndex();
    if(state->getStateIndex()==Index::WalkingState&&xSpeed==0)switchToIdleState();
    x+=xSpeed;
    y+=ySpeed;
    if(!isOnGround()){
        ySpeed+=2;
    }else if(ySpeed>0){
        ySpeed=0;
        y=groundY;
    }
    state->updateFrame(this);//更新当前状态的帧页面
    emit frameUpdate(state->getStateIndex(),state->getCurrentFrame(),x,y);//发送信号给fighter.让其改变动画
}

void Character::switchToJumpingState(){
    if(state->getStateIndex()==Index::IdleState||state->getStateIndex()==Index::WalkingState){
        delete state;
        state=new JumpingState(this);
        ySpeed=-20;
    }
}

void Character::switchToWalkingState(int vx){
    if(state->getStateIndex()==Index::IdleState){
        delete state;
        state=new WalkingState(this);
        //修改速度
        xSpeed=vx;
        //修改朝向
        characterDir=vx>0?direction::right:direction::left;
    }
}

void Character::switchToAttackingState(){
    if(state->getStateIndex()==Index::IdleState||state->getStateIndex()==Index::WalkingState){
        //攻击时速度/=2，朝向不变
        xSpeed/=2;
        delete state;
        state=new AttackingState(this);
    }
}

void Character::switchToDefendingState(){
    if(state->getStateIndex()==Index::IdleState||state->getStateIndex()==Index::WalkingState){
        //防御的时候x速度立马清0
        xSpeed=0;
        delete state;
        state=new DefendingState(this);
    }
}

void Character::switchToIdleState(){
    delete state;
    state = new IdleState(this);
}
