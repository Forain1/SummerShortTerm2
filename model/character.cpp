#include "character.h"
#include "characterstate.h"

Character::Character(int x,int y,QObject *parent)
    : QObject{parent},maxHealth{100},currentHealth{100},x(x),y(y)
{
   state=new IdleState(this);

}

void Character::nextFrame(){
    state->updateFrame(this);
    x+=xSpeed;
    y+=ySpeed;
    emit frameUpdate(state->getStateIndex(),state->getCurrentFrame(),x,y);
}
