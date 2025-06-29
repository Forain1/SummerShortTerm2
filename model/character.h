#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>

class CharacterState;

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(QObject *parent = nullptr);
    void setCurrentHealth(int delta){currentHealth+=delta;}
    void setCoordinate(double deltaX,double deltaY){x+=deltaX;y+=deltaY;}
    void setSpeed(double deltaX,double deltaY){xSpeed+=deltaX,ySpeed+=deltaY;}

    int getCurrentHealth(){return currentHealth;}
    int getX(){return x;}
    int getY(){return y;}
    int getSpeedX(){return xSpeed;}
    int getSpeedY(){return ySpeed;}
private:
    int maxHealth;//最大生命值
    int currentHealth;//当前生命值
    CharacterState *state;//角色状态：Idle,Jumping,Falling...
    double x,y;//角色坐标
    double xSpeed,ySpeed;
signals:
};

#endif // CHARACTER_H
