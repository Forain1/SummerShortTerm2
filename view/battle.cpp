#include "battle.h"
#include <QGraphicsScene>
#include <QScrollBar>
#include <QGraphicsRectItem>
#define BATTLEWIDTH 1586
#define BATTLEHEIGHT 886
Battle::Battle(QWidget* parent,QString path,int role0Num,int role1Num):QGraphicsView(parent) {

    //设置view的大小
    this->setFixedSize(BATTLEWIDTH,BATTLEHEIGHT);
    //设置scene的大小
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,BATTLEWIDTH,BATTLEHEIGHT);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    // 禁止活动栏的出现
    setViewportMargins(0, 0, 0, 0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    loadBackground(path);
    //生成对应模型的角色
    fighter0 = new Fighter(nullptr,role0Num);
    fighter1 = new Fighter(nullptr,role1Num,false);
    //添加进入场景 并设置在场景的坐标位置
    scene->addItem(fighter0);
    fighter0->setPos(20,BATTLEHEIGHT-fighter0->getHeight());
    scene->addItem(fighter1);
    fighter1->setPos(BATTLEWIDTH-20-fighter1->getWidth(),BATTLEHEIGHT-fighter1->getHeight());

    //由于view大于所提供的窗口 在这里把窗口拉到最下方
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
    this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->minimum());
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

int Battle::getWidth(int num){
    if(num==0){
        return fighter0->getWidth();
    }else if(num==1){
        return fighter1->getWidth();
    }else{
        return 0;
    }
}

int Battle::getHeight(int num){
    if(num==0){
        return fighter0->getHeight();
    }else if(num==1){
        return fighter1->getHeight();
    }else{
        return 0;
    }
}
