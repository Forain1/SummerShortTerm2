#ifndef FIGHTER_H
#define FIGHTER_H
#include <QGraphicsObject>
#include <QList>
#include <QTimer>
class Fighter:public QGraphicsObject
{
    Q_OBJECT
public:
    Fighter(QGraphicsItem* parent=nullptr,int roleNum=0);
public slots:
    void nextFrame();

private:
    QList<QPixmap> idleFrames;
    int currentFrame=0;
    QTimer timer;
};

#endif // FIGHTER_H
