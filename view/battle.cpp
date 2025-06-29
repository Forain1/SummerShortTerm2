#include "battle.h"
#include <QGraphicsScene>

Battle::Battle(QWidget* parent,QString path,int role0Num,int role1Num):QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1600,900);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    // 禁止活动栏的出现
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    loadBackground(path);
    //生成对应模型的角色
}

Battle::~Battle(){}

void Battle::loadBackground(const QString& imagePath)
{
    QPixmap bgPixmap(imagePath);
    if (bgPixmap.isNull()) return;

    QPixmap scaled = bgPixmap.scaled(scene->sceneRect().size().toSize(),
                                     Qt::KeepAspectRatioByExpanding);
    bgItem = scene->addPixmap(scaled);
    bgItem->setZValue(-1);
    bgItem->setPos(0, 0);
    bgItem->setEnabled(false);
}
