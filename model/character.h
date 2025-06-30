#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include "../common/index.h"
class CharacterState;

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(int x,int y,QObject *parent = nullptr);
    void setCurrentHealth(int delta){currentHealth+=delta;}
    void setCoordinate(int deltaX,int deltaY){x+=deltaX;y+=deltaY;emit CoordinateUpdate(x,y);}
    void setSpeed(int deltaX,int deltaY){xSpeed+=deltaX,ySpeed+=deltaY;}
    void setCharacterState(CharacterState *nextState){state=nextState;}

    int getCurrentHealth(){return currentHealth;}
    CharacterState *getState(){return state;};
    int getX(){return x;}
    int getY(){return y;}
    int getSpeedX(){return xSpeed;}
    int getSpeedY(){return ySpeed;}
private:
    int maxHealth;//最大生命值
    int currentHealth;//当前生命值
    CharacterState *state;//角色状态：Idle,Jumping,Falling...
    int x,y;//角色坐标
    int xSpeed,ySpeed;//x,y方向速度

signals:
    void CoordinateUpdate(int x,int y);
    void frameUpdate(Index::StateIndex stateIndex,int frame);

public slots:
    void nextFrame();
};

#endif // CHARACTER_H
