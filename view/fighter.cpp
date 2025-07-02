#include"fighter.h"
#include<QPainter>
#include<QTransform>

Fighter::Fighter(QGraphicsItem* parent,int roleNum,bool left):QGraphicsObject(parent) {
    //初始化角色图片的朝向
    if(left)currentDir = Index::rightIndex;
    else currentDir = Index::leftIndex;

    if(roleNum==0){
        frames.resize(6);
        qDebug()<<"loading image";
        for(int i = 0 ;i < 6; i++){
            QPixmap pix;
            QString path = ":/src/image" + QString::number(i) +".png";
            pix.load(path);
            if(!pix.isNull()){
                frames[Index::WalkingState].append(pix);
                frames[Index::IdleState].append(pix);
                frames[Index::JumpingState].append(pix);
                frames[Index::DefendingState].append(pix);
                frames[Index::AttackingState].append(pix);
                frames[Index::FallingState].append(pix);
              qDebug()<<"success:"<<i;
            }

        }
    }
}

void Fighter::nextFrame(Index::StateIndex state , int frame ,int x ,int y,Index::DirectionIndex characterDir){
    currentState = state;
    currentFrame = frame;
    currentDir = characterDir;
    this->setPos(x,y);
    update();
}

QRectF Fighter::boundingRect() const{
    return QRectF(0,0,frames[currentState][currentFrame].width(),frames[currentState][currentFrame].height());
}

void Fighter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(currentDir==Index::rightIndex){
        //图像默认存储格式朝左,若角色此时朝向为右,则需展示翻转后的图片
        QTransform trans;
        trans.scale(-1,1);
        QPixmap flipPix = frames[currentState][currentFrame].transformed(trans);
        painter->drawPixmap(0,0,flipPix);
    }else painter->drawPixmap(0,0,frames[currentState][currentFrame]);
}

int Fighter::getWidth()const{
    return frames[currentState][currentFrame].width();
}

int Fighter::getHeight()const{
    return frames[currentState][currentFrame].height();
}
