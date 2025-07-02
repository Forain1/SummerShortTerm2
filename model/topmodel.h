#ifndef TOPMODEL_H
#define TOPMODEL_H

#include <QObject>
class Character;
class SceneState;

class TopModel : public QObject
{
    Q_OBJECT
public:
    explicit TopModel(QObject *parent = nullptr);
    Character *getCharacter0() const {return c0;}
    Character *getCharacter1() const {return c1;}
    SceneState *getSceneState() const {return sceneState;}
private:
    Character *c0;
    Character *c1;

    SceneState *sceneState;
signals:

public slots:
    void getSize(int c0Width,int c0Height,int c1Width,int c1Height);
};

#endif // TOPMODEL_H
