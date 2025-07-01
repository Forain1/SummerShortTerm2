#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include "../common/index.h"
#define groundY 400;
class CharacterState;

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(int x,int y,QObject *parent = nullptr);

    void setCurrentHealth(int delta){currentHealth+=delta;}
    void setCharacterState(CharacterState *nextState){state=nextState;}
    void setXSpeed(int x){xSpeed=x;}
    void setYSpeed(int y){ySpeed=y;}

    int getCurrentHealth(){return currentHealth;}
    CharacterState *getState(){return state;};
    int getX(){return x;}
    int getY(){return y;}
    int getSpeedX(){return xSpeed;}
    int getSpeedY(){return ySpeed;}

    bool isOnGround(){return y>=groundY;}

    //可以由键盘输入决定的状态转换
    //idle,walk->jump
    void switchToJumpingState();
    //idle->walk
    void switchToWalkingState(int vx);
    //idle,walk->defend
    void switchToDefendingState();
    //idle,walk->attack
    void switchToAttackingState();
private:
    int maxHealth;//最大生命值
    int currentHealth;//当前生命值
    CharacterState *state;//角色状态：Idle,Jumping,Falling...
    int x,y;//角色坐标
    int xSpeed=0,ySpeed=0;//x,y方向速度
    enum direction{
        left,right
    };
    direction characterDir;

signals:
    void frameUpdate(Index::StateIndex stateIndex,int frame,int x,int y);

public slots:
    void nextFrame();
};

#endif // CHARACTER_H
