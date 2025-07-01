#include"fighter.h"
#include<QPainter>


Fighter::Fighter(QGraphicsItem* parent,int roleNum,bool left):QGraphicsObject(parent) {
    if(roleNum==0){
        frames.resize(3);
        qDebug()<<"loading image";
        for(int i = 0 ;i < 6; i++){
            QPixmap pix;
            QString path = ":/src/image" + QString::number(i) +".png";
            pix.load(path);
            if(!pix.isNull()){
                frames[Index::IdleState].append(pix);
              qDebug()<<"success:"<<i;
            }

        }
    }
}

void Fighter::nextFrame(Index::StateIndex state , int frame ,int x ,int y){
    currentState = state;
    currentFrame = frame;
    this->setPos(x,y);
     qDebug()<<"current:"<<x<<" "<<y;
    update();
}

QRectF Fighter::boundingRect() const{
    return QRectF(0,0,frames[currentState][currentFrame].width(),frames[currentState][currentFrame].height());
}

void Fighter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0,frames[currentState][currentFrame]);
}

int Fighter::getWidth()const{
    return frames[currentState][currentFrame].width();
}

int Fighter::getHeight()const{
    return frames[currentState][currentFrame].height();
}
