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
    void pressKeyA();
    void pressKeyD();
};

#endif // FIGHTERCONTROLLER_H
