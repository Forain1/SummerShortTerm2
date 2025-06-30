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
    fighter0 = new Fighter(nullptr,role0Num);
    fighter1 = new Fighter(nullptr,role1Num,false);
    //添加进入场景 并设置在场景的坐标位置
    scene->addItem(fighter0);
    fighter0->setPos(20,900-fighter0->getHeight());
    scene->addItem(fighter1);
    fighter1->setPos(1600-20-fighter1->getWidth(),900-fighter1->getHeight());
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
