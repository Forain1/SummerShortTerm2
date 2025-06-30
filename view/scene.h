#ifndef SCENE_H
#define SCENE_H

#include <QWidget>

class Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr,QString path="");//需要传入背景图
signals:

protected:
    void paintEvent(QPaintEvent* event);
private:
    QString bgPath;
    QPixmap bg;
};

#endif // SCENE_H
