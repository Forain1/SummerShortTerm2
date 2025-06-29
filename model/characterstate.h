#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

#include <QObject>

class CharacterState : public QObject
{
    Q_OBJECT
public:
    explicit CharacterState(QObject *parent = nullptr);
    virtual ~CharacterState() = default;

    virtual void updateFrame(const QString &newAction) = 0;//切换至下一帧
    virtual QString getStateName() const = 0;//获取状态名
private:
    int frame;//记录当前帧数
signals:
};

class IdleState : public CharacterState
{
    explicit IdleState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(const QString &newAction) override;
    QString getStateName() const override{return "Idle";}
};

class WalkingState:public CharacterState
{
    explicit WalkingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(const QString &newAction) override;
    QString getStateName() const override{return "Walking";}
};

class JumpingState:public CharacterState
{
    explicit JumpingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(const QString &newAction) override;
    QString getStateName() const override{return "Jumping";}
};

class FallingState:public CharacterState
{
    explicit FallingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(const QString &newAction) override;
    QString getStateName() const override{return "Falling";}
};

class AttackingState:public CharacterState
{
    explicit AttackingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(const QString &newAction) override;
    QString getStateName() const override{return "Attacking";}
};

class DefendingState:public CharacterState
{
    explicit DefendingState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(const QString &newAction) override;
    QString getStateName() const override{return "Defending";}
};

class StunnedState:public CharacterState
{
    explicit StunnedState(QObject *parent=nullptr) : CharacterState(parent){}
    void updateFrame(const QString &newAction) override;
    QString getStateName() const override{return "Stunned";}
};
#endif // CHARACTERSTATE_H
