#include"fighter.h"
#include<QPainter>
#include<QTransform>
#define RECWIDTH 400
#define RECHEIGHT 200

Fighter::Fighter(QGraphicsItem* parent,int roleNum,bool left):QGraphicsObject(parent) {
    //初始化角色图片的朝向
    if(left)currentDir = Index::rightIndex;
    else currentDir = Index::leftIndex;

    if(roleNum==0){
        frames.resize(6);
        qDebug()<<"loading image";
        loadAnimation("Idle",6);
        loadAnimation("Jump",6);
        loadAnimation("Attack",6);
        loadAnimation("Defend",4);
        loadAnimation("Fall",4);
        loadAnimation("Rush",9);
    }
}

void Fighter::loadAnimation(QString state,int maxFrame){
    int index=-1;
    if(state == "Idle") index = Index::IdleState;
    else if(state == "Jump") index = Index::JumpingState;
    else if(state == "Rush") index = Index::WalkingState;
    else if(state == "Attack") index = Index::AttackingState;
    else if(state == "Defend") index = Index::DefendingState;
    else if(state == "Fall") index = Index::FallingState;
    if(index>=0){
        for(int i = 0 ;i < maxFrame; i++){
            QPixmap pix;
            QString path = ":/src/Character/" +state+"/"+QString::number(i) +".png";
            pix.load(path);
            if(!pix.isNull()){
                frames[index].append(pix);
            }
        }
    }
}

void Fighter::nextFrame(Index::StateIndex state , int frame ,int x ,int y,Index::DirectionIndex characterDir){
    currentState = state;
    currentFrame = frame;
    currentDir = characterDir;
    this->setPos(x-frames[currentState][currentFrame].width()/2,y-frames[currentState][currentFrame].height());
    update();
}

QRectF Fighter::boundingRect() const{
    return QRectF(0,0,RECWIDTH,RECHEIGHT);
}

void Fighter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(currentDir==Index::leftIndex){
        //图像默认存储格式朝右,若角色此时朝向为左,则需展示翻转后的图片
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
