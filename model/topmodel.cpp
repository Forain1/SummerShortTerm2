#include "topmodel.h"
#include "../model/character.h"
#include "../model/scenestate.h"
#include "../common/index.h"

#include <QDebug>

TopModel::TopModel(QObject *parent)
    : QObject{parent}
{
    sceneState=new SceneState(this);
    c0 = new Character(Index::rightIndex,this);
    c1 = new Character(Index::leftIndex,this);
}

void TopModel::getSize(int c0Width,int c0Height,int c1Width,int c1Height){
    qDebug()<<"111";
    c0->setIdleWidth(c0Width);
    c0->setIdleHeight(c0Height);
    c1->setIdleWidth(c1Width);
    c1->setIdleHeight(c1Height);

    c0->setWidth(c0Width);
    c0->setHeight(c0Height);
    c1->setWidth(c1Width);
    c1->setHeight(c1Height);

    c0->setX(20);
    c0->setY(BATTLEHEIGHT-c0Height);
    c1->setX(BATTLEWIDTH-20-c1Width);
    c1->setY(BATTLEHEIGHT-c1Height);

    c0->setGroundY(BATTLEHEIGHT-c0Height);
    c1->setGroundY(BATTLEHEIGHT-c1Height);
}
