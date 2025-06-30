#include "character.h"
#include "characterstate.h"

Character::Character(int x,int y,QObject *parent)
    : QObject{parent},maxHealth{100},currentHealth{100},x(x),y(y)
{
   state=new IdleState(this);
}

void Character::nextFrame(){
    state->updateFrame(this);
}
