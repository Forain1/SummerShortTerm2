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
    }
}
//落地时，如果初速度为0，切换为idle;反之切换为walking
void FallingState::updateFrame(Character *parent){
    if(parent->isOnGround()){
        if(parent->getSpeedX()==0){
            parent->setCharacterState(new IdleState());
        }else{
            parent->setCharacterState(new WalkingState());
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
    int maxFrame = getMaxFrame();
    int curFrame = getCurrentFrame();
    int baseWidth = parent->getIdleWidth();
    int attackInc = parent->getAttackWidthInc(); // 攻击最大增量

    // 动态调整width
    int newWidth = baseWidth + (attackInc * curFrame) / (maxFrame > 0 ? maxFrame : 1);
    parent->setWidth(newWidth);

    if(curFrame < maxFrame){
        currentFrame++;
    }else{
        parent->setWidth(baseWidth); // 恢复原始宽度
        parent->setCharacterState(new IdleState());
    }
}
