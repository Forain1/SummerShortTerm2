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
    emit frameUpdate(state->getStateIndex(),state->getCurrentFrame(),x,y,characterDir,currentHealth);//发送信号给fighter.让其改变动画
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

void Character::handleC0LeftMove(){
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

void Character::handleC0RightMove(){
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

void Character::handleC0Jump(){
    switchToJumpingState();
}

void Character::handleC0Defend(){
    switchToDefendingState();
}

void Character::handleC1LeftMove(){
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

void Character::handleC1RightMove(){
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

void Character::handleC1Jump(){
    switchToJumpingState();
}

void Character::handleC1Defend(){
    switchToDefendingState();
}

void Character::handleC0StopLeftMove(){
    aPressed = false;
    if(!aPressed&&!dPressed){
        setXSpeed(0);
    }
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleC0StopRightMove(){
    dPressed = false;
    if(!aPressed&&!dPressed){
        setXSpeed(0);
    }
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleC0StopDefend(){
    if(getState()->getStateIndex()==Index::DefendingState){
        setCharacterState(new IdleState());
    }
}

void Character::handleC1StopLeftMove(){
    leftPressed = false;
    if(!leftPressed&&!rightPressed){
        setXSpeed(0);
    }
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleC1StopRightMove(){
    rightPressed = false;
    if(!leftPressed&&!rightPressed){
        setXSpeed(0);
    }
    if (getState()->getStateIndex() == Index::WalkingState) {
        setCharacterState(new IdleState());
    }
}

void Character::handleC1StopDefend(){
    if(getState()->getStateIndex()==Index::DefendingState){
        setCharacterState(new IdleState());
    }
}
