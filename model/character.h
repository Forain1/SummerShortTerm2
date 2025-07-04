#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include "../common/index.h"
class CharacterState;

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(Index::DirectionIndex characterDir,QObject *parent = nullptr);

    void setCurrentHealth(int h){currentHealth=h;emit healthUpdate(h);}
    void setCharacterState(CharacterState *nextState);
    void setX(int xcoordinate){x=xcoordinate;}
    void setY(int ycoordinate){y=ycoordinate;}
    void setXSpeed(int x){xSpeed=x;}
    void setYSpeed(int y){ySpeed=y;}
    void setIdleWidth(int w){idleWidth=w;}
    void setIdleHeight(int h){idleHeight=h;}
    void setWidth(int w){width=w;}
    void setHeight(int h){height=h;}
    void setGroundY(int y){groundY=y;}
    void setHasHit(bool v){hasHit=v;}
    void setAttackWidth(int w){attackWidth=w;}
    void setDirection(Index::DirectionIndex direction){characterDir=direction;}

    int getCurrentHealth() const {return currentHealth;}
    CharacterState *getState() const {return state;};
    int getX() const {return x;}
    int getY() const {return y;}
    int getSpeedX() const {return xSpeed;}
    int getSpeedY() const {return ySpeed;}
    int getIdleWidth() const {return idleWidth;}
    int getIdleHeight() const {return idleHeight;}
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    int getAttackWidthInc() const {return attackWidthInc;}
    int getAttackWidth() const {return attackWidth;}
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
    //由topmodel层进行调用
    void nextFrame();

    bool getHasHit() const { return hasHit; }

private:
    int maxHealth;//最大生命值
    int currentHealth;//当前生命值
    CharacterState *state;//角色状态：Idle,Jumping,Falling...
    int x,y;//角色坐标
    int xSpeed=0,ySpeed=0;//x,y方向速度
    int groundY;
    Index::DirectionIndex characterDir;
    bool leftPressed = false;
    bool rightPressed = false;

    int idleWidth;
    int idleHeight;
    int width;
    int height;
    int attackWidthInc=100;
    int attackWidth;
    bool hasHit = false;

public slots:
    void handleLeftMove();
    void handleRightMove();
    void handleJump();
    void handleDefend();
    void handleAttack();
    void handleStopLeftMove();
    void handleStopRightMove();
    void handleStopDefend();


signals:
    void frameUpdate(Index::StateIndex stateIndex,int frame,int x,int y,Index::DirectionIndex characterDir);
    void healthUpdate(int currentHealth);
};

#endif // CHARACTER_H
