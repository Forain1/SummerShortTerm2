#include "character.h"
#include "characterstate.h"
#include <QDebug>
Character::Character(int x,int y,QObject *parent)
    : QObject{parent},maxHealth{100},currentHealth{100},x(x),y(y)
{
    state=new IdleState(this);
    groundY=y;
}

void Character::setCharacterState(CharacterState *nextState){
    CharacterState *tempState=state;
    state=nextState;
    delete tempState;
}

void Character::nextFrame(){
    qDebug()<<"xspeed:"<<xSpeed<<"state"<<state->getStateIndex();
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
        setCharacterState(new JumpingState(this));
        ySpeed=-20;
    }
}

void Character::switchToWalkingState(int vx){
    if(state->getStateIndex()==Index::IdleState){
        setCharacterState(new WalkingState(this));
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
        setCharacterState(new AttackingState(this));
    }
}

void Character::switchToDefendingState(){
    if(state->getStateIndex()==Index::IdleState||state->getStateIndex()==Index::WalkingState){
        //防御的时候x速度立马清0
        xSpeed=0;
        setCharacterState(new DefendingState(this));
    }
}

void Character::switchToIdleState(){
    if(state->getStateIndex()==Index::WalkingState||state->getStateIndex()==Index::DefendingState){
        setCharacterState(new IdleState(this));
        xSpeed=0;
    }
}

void Character::handlePressKeyA(){
    if(!aPressed){
        aPressed=true;
        if(getState()->getStateIndex()==Index::JumpingState||getState()->getStateIndex()==Index::FallingState){
            setXSpeed(-10);
        }
        else if(true){//需要在这里检测碰撞
            switchToWalkingState(-10);
        }
    }
}

void Character::handlePressKeyD(){
    if(!dPressed){
        dPressed=true;
        if(getState()->getStateIndex()==Index::JumpingState||getState()->getStateIndex()==Index::FallingState){
            setXSpeed(10);
        }
        else if(true){//需要检测碰撞
            switchToWalkingState(10);
        }
    }
}

void Character::handlePressKeyW(){
    switchToJumpingState();
}

void Character::handlePressKeyS(){
    switchToDefendingState();
}

void Character::handlePressKeyLeft(){
    if(!leftPressed){
        leftPressed=true;
        if(getState()->getStateIndex()==Index::JumpingState||getState()->getStateIndex()==Index::FallingState){
            setXSpeed(-10);
        }
        else if(true){
            switchToWalkingState(-10);
        }
    }
}

void Character::handlePressKeyRight(){
    if(!rightPressed){
        rightPressed=true;
        if(getState()->getStateIndex()==Index::JumpingState||getState()->getStateIndex()==Index::FallingState){
            setXSpeed(10);
        }
        if(true){
            switchToWalkingState(10);
        }
    }
}

void Character::handlePressKeyUp(){
    switchToJumpingState();
}

void Character::handlePressKeyDown(){
    switchToDefendingState();
}

void Character::handleReleaseKeyA(){
    aPressed = false;
    setXSpeed(0);
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleReleaseKeyD(){
    dPressed = false;
    setXSpeed(0);
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleReleaseKeyS(){
    if(getState()->getStateIndex()==Index::DefendingState){
        setCharacterState(new IdleState());
    }
}

void Character::handleReleaseKeyLeft(){
    leftPressed = false;
    setXSpeed(0);
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleReleaseKeyRight(){
    rightPressed = false;
    setXSpeed(0);
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleReleaseKeyDown(){
    if(getState()->getStateIndex()==Index::DefendingState){
        setCharacterState(new IdleState());
    }
}
