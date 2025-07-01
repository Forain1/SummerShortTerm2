#ifndef FIGHTERCONTROLLER_H
#define FIGHTERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include "../view/battle.h"
#include "../model/character.h"
class FighterController : public QObject
{
    Q_OBJECT
public:
    explicit FighterController(Battle* battle,QObject *parent = nullptr);
protected:
    bool eventFilter(QObject* obj,QEvent* event);
private:
    QTimer *timer;
    Battle* battle;
    Character *c0,*c1;
    // 按键状态
    bool aPressed = false;
    bool dPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
    void pressKeyA();
    void pressKeyD();
    void pressKeyS();
    void pressKeyW();
    void pressKeyLeft();
    void pressKeyRight();
    void pressKeyUp();
    void pressKeyDown();

};

#endif // FIGHTERCONTROLLER_H
