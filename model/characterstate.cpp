#include "characterstate.h"

CharacterState::CharacterState(QObject *parent)
    : QObject{parent},currentFrame{0}
{}

void IdleState::updateFrame(Character *parent){
    if(currentFrame<getMaxFrame()){
        currentFrame++;
    }else{
        currentFrame=0;
    }
}

void WalkingState::updateFrame(Character *parent){
    if(currentFrame<getMaxFrame()){
        currentFrame++;
    }else{
        currentFrame=0;
    }
}
//假设跳跃没有动画只有一帧
void JumpingState::updateFrame(Character *parent){
    if(parent->getSpeedY()<=0){
        parent->setCharacterState(new FallingState());
        delete this;
    }
}
//落地时，如果初速度为0，切换为idle;反之切换为walking
void FallingState::updateFrame(Character *parent){
    if(parent->isOnGround()){
        // 延迟一帧再检查，确保按键输入被正确处理
        if(currentFrame == 0) {
            currentFrame = 1;
            return;
        }
        
        if(parent->getSpeedX()==0){
            parent->setCharacterState(new IdleState());
        }else{
            parent->setCharacterState(new WalkingState());
        }
        delete this;
    } else {
        if(currentFrame<getMaxFrame()){
            currentFrame++;
        }else{
            currentFrame=0;
        }
    }
}

void DefendingState::updateFrame(Character *parent){
    if(currentFrame<getMaxFrame()){
        currentFrame++;
    }else{
        currentFrame=0;
    }
}

void AttackingState::updateFrame(Character *parent){
    if(currentFrame<getMaxFrame()){
        currentFrame++;
    }else{
        parent->setCharacterState(new IdleState());
        delete this;
    }
}
