#include"fighter.h"

Fighter::Fighter(QGraphicsItem* parent,int roleNum):QGraphicsObject(parent) {
    if(roleNum==0){
        for(int i = 0 ;i < 6; i++){
            QPixmap pix;
            QString path = ":/src/image" + QString::number(i) +".jpg";
            pix.load(path);
            idleFrames.append(pix);
        }
    }
    if (!idleFrames.isEmpty()) {
        timer.setInterval(100); // 每100ms切换一帧，可调节速度
        connect(&timer, &QTimer::timeout, this, &Fighter::nextFrame);
        timer.start();
    }
}

void Fighter::nextFrame(){
    ++currentFrame %= idleFrames.size();
}
