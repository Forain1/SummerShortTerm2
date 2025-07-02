#include "showhealth.h"
#include <QPainter>

ShowHealth::ShowHealth(int health):health(health) {}


QRectF ShowHealth::boundingRect()const{
    return QRectF(0,0,HEALTHWIDTH,HEALTHHEIGHT);
}

void ShowHealth::paint(QPainter* painter ,const QStyleOptionGraphicsItem * option,QWidget * widget){
    painter->setPen(Qt::black);
    painter->drawRect(0,0,HEALTHWIDTH,HEALTHHEIGHT);
    painter->drawText(boundingRect(),QString::number(health));
}

void ShowHealth::changeHealth(int newHealth){
    if(newHealth!=health){
        health = newHealth;
        update();
    }
}
