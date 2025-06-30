#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>

class CharacterState;

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(int x,int y,QObject *parent = nullptr);
    void setCurrentHealth(int delta){currentHealth+=delta;}
    void setCoordinate(int deltaX,int deltaY){x+=deltaX;y+=deltaY;}
    void setSpeed(int deltaX,int deltaY){xSpeed+=deltaX,ySpeed+=deltaY;}
    void setCharacterState(CharacterState *nextState){state=nextState;}

    int getCurrentHealth(){return currentHealth;}
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
    int currentFrame;//当前状态播放到第几帧

signals:
};

#endif // CHARACTER_H
