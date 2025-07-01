#include "character.h"
#include "characterstate.h"

Character::Character(int x,int y,QObject *parent)
    : QObject{parent},maxHealth{100},currentHealth{100},x(x),y(y)
{
   state=new IdleState(this);

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
    state->updateFrame(this);
    emit frameUpdate(state->getStateIndex(),state->getCurrentFrame(),x,y);
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
