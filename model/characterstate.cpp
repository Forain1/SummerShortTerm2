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
    emit parent->frameUpdate(Index::IdleState,currentFrame);
}
