#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

#include <QObject>
#include "character.h"
#include "../common/index.h"

class CharacterState : public QObject
{
    Q_OBJECT
public:
    explicit CharacterState(QObject *parent = nullptr);
    virtual ~CharacterState() = default;

    virtual void updateFrame(Character *parent) = 0;//切换至下一帧
    virtual Index::StateIndex getStateIndex() const = 0;//获取状态名
    int getCurrentFrame() const{return currentFrame;}//获取当前动画在第几帧
    virtual int getMaxFrame() const = 0;//获取状态动画的总帧数
protected:
    int currentFrame=0;//记录当前帧数
};

class IdleState : public CharacterState
{
public:
    explicit IdleState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(Character *parent) override;
    Index::StateIndex getStateIndex() const override{return Index::IdleState;}
    int getMaxFrame() const override{return 5;}
};

class WalkingState:public CharacterState
{
public:
    explicit WalkingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(Character *parent) override;
    Index::StateIndex getStateIndex() const override{return Index::WalkingState;}
    int getMaxFrame() const override{return 8;}
};

class JumpingState:public CharacterState
{
public:
    explicit JumpingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(Character *parent) override;
    Index::StateIndex getStateIndex() const override{return Index::JumpingState;}
    int getMaxFrame() const override{return 5;}
};

class FallingState:public CharacterState
{
public:
    explicit FallingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(Character *parent) override;
    Index::StateIndex getStateIndex() const override{return Index::FallingState;}
    int getMaxFrame() const override{return 3;}
};

class AttackingState:public CharacterState
{
public:
    explicit AttackingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(Character *parent) override;
    Index::StateIndex getStateIndex() const override{return Index::AttackingState;}
    int getMaxFrame() const override{return 5;}
};

class DefendingState:public CharacterState
{
public:
    explicit DefendingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(Character *parent) override;
    Index::StateIndex getStateIndex() const override{return Index::DefendingState;}
    int getMaxFrame() const override{return 3;}
};

class StunnedState:public CharacterState
{
public:
    explicit StunnedState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(Character *parent) override;
    Index::StateIndex getStateIndex() const override{return Index::StunnedState;}
    int getMaxFrame() const override{return 0;}
};
#endif // CHARACTERSTATE_H
