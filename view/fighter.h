#ifndef FIGHTER_H
#define FIGHTER_H
#include <QGraphicsObject>
#include <QList>
#include <QTimer>
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
    void nextFrame();

private:
    enum state{
        idle,move,jump
    };
    QList<QList<QPixmap>> frames;
    int currentFrame=0;
    int currentState=idle;
    QTimer timer;
};

#endif // FIGHTER_H
