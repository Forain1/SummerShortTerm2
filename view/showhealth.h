#ifndef SHOWHEALTH_H
#define SHOWHEALTH_H

#include <QObject>
#include <QGraphicsItem>
#define HEALTHWIDTH 100
#define HEALTHHEIGHT 100

class ShowHealth:public QGraphicsItem
{
public:
    ShowHealth(int health=100);
    QRectF boundingRect()const override;
    void paint(QPainter* ,const QStyleOptionGraphicsItem * ,QWidget *) override;
public slots:
    void changeHealth(int);
private:
    int health;

};

#endif // SHOWHEALTH_H
