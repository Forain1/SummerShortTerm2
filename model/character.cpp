#include "character.h"
#include "characterstate.h"
#include <QDebug>

Character::Character(Index::DirectionIndex direction,QObject *parent)
    : QObject{parent},maxHealth{100},currentHealth{100}
{
    state=new IdleState(this);
    characterDir=direction;
}

void Character::setCharacterState(CharacterState *nextState){
    CharacterState *tempState=state;
    state=nextState;
    delete tempState;
}

void Character::nextFrame(){
    x+=xSpeed;
    y+=ySpeed;
    if(!isOnGround()){
        ySpeed+=2;
    }else if(ySpeed>0){
        ySpeed=0;
        y=groundY;
    }
    state->updateFrame(this);//更新当前状态的帧页面
    //如果速度不为0，修改朝向
    if(xSpeed!=0){
        characterDir=xSpeed>0?Index::rightIndex : Index::leftIndex;
    }
    emit frameUpdate(state->getStateIndex(),state->getCurrentFrame(),x,y,characterDir);//发送信号给fighter.让其改变动画
}

void Character::switchToJumpingState(){
    if(state->getStateIndex()==Index::IdleState||state->getStateIndex()==Index::WalkingState){
        setCharacterState(new JumpingState(this));
        ySpeed=-20;
    }
}

void Character::switchToWalkingState(int vx){
    if(state->getStateIndex()==Index::IdleState||state->getStateIndex()==Index::WalkingState){
        setCharacterState(new WalkingState(this));
        //修改速度
        xSpeed=vx;
    }
}

void Character::switchToAttackingState(){
    if(state->getStateIndex()==Index::IdleState||state->getStateIndex()==Index::WalkingState){
        xSpeed/=4;
        setCharacterState(new AttackingState(this));
        hasHit = false;
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

void Character::handleLeftMove(){
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

void Character::handleRightMove(){
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

void Character::handleJump(){
    switchToJumpingState();
}

void Character::handleDefend(){
    switchToDefendingState();
}

void Character::handleAttack(){
    switchToAttackingState();
}

void Character::handleStopLeftMove(){
    leftPressed = false;
    if(!leftPressed&&!rightPressed){
        setXSpeed(0);
    }
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleStopRightMove(){
    rightPressed = false;
    if(!leftPressed&&!rightPressed){
        setXSpeed(0);
    }
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleStopDefend(){
    if(getState()->getStateIndex()==Index::DefendingState){
        setCharacterState(new IdleState());
    }
}
