#ifndef FIGHTER_H
#define FIGHTER_H
#include <QGraphicsObject>
#include <QList>
#include "../common/index.h"


class Fighter:public QGraphicsObject
{
    Q_OBJECT
public:
    Fighter(QGraphicsItem* parent=nullptr,int roleNum=0,bool left=true);
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    int getWidth() const;
    int getHeight() const;
public slots:
    void nextFrame(Index::StateIndex state,int frame,int x,int y,Index::DirectionIndex characterDir);//state表示要播放哪个数组的动画,frame表示是该动画的第几帧
private:
    QList<QList<QPixmap>> frames;
    int currentFrame=0;
    Index::DirectionIndex currentDir;
    Index::StateIndex currentState=Index::IdleState;
};

#endif // FIGHTER_H
