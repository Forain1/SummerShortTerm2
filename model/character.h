#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include "../common/index.h"
class CharacterState;

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(int x,int y,Index::DirectionIndex characterDir,QObject *parent = nullptr);

    void setCurrentHealth(int delta){currentHealth+=delta;}
    void setCharacterState(CharacterState *nextState);
    void setXSpeed(int x){xSpeed=x;}
    void setYSpeed(int y){ySpeed=y;}

    int getCurrentHealth() const {return currentHealth;}
    CharacterState *getState() const {return state;};
    int getX() const {return x;}
    int getY() const {return y;}
    int getSpeedX() const {return xSpeed;}
    int getSpeedY() const {return ySpeed;}
    Index::DirectionIndex getDirection() const {return characterDir;}

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
    //walk,defend->idle
    void switchToIdleState();
private:
    int maxHealth;//最大生命值
    int currentHealth;//当前生命值
    CharacterState *state;//角色状态：Idle,Jumping,Falling...
    int x,y;//角色坐标
    int xSpeed=0,ySpeed=0;//x,y方向速度
    int groundY;
    Index::DirectionIndex characterDir;
    bool aPressed = false;
    bool dPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

public slots:
    void handlePressKeyA();
    void handlePressKeyD();
    void handlePressKeyS();
    void handlePressKeyW();
    void handlePressKeyLeft();
    void handlePressKeyRight();
    void handlePressKeyUp();
    void handlePressKeyDown();
    void handleReleaseKeyA();
    void handleReleaseKeyD();
    void handleReleaseKeyS();
    void handleReleaseKeyLeft();
    void handleReleaseKeyRight();
    void handleReleaseKeyDown();


signals:
    void frameUpdate(Index::StateIndex stateIndex,int frame,int x,int y,Index::DirectionIndex characterDir);

public slots:
    void nextFrame();
};

#endif // CHARACTER_H
