#ifndef BATTLE_H
#define BATTLE_H
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include"fighter.h"
class Battle: public QGraphicsView
{
    Q_OBJECT
public:
    //需要传入四个参数,第二个是该场景的背景图路径,第三个和第四个是角色模型的编号,这样一来才可以加载对应角色的图示
    explicit Battle(QWidget* parent = nullptr,QString bgpath="",int role0Num=0,int role1Num=0);
    ~Battle();
    //返回num指向的角色的长宽
    int getWidth(int num);
    int getHeight(int num);
public slots:
    void setCoodinate(int roleNum,int x,int y);
private:
    void loadBackground(const QString& path);
    QGraphicsScene* scene;
    QGraphicsPixmapItem* bgItem;
    Fighter* fighter0,*fighter1;


};

#endif // BATTLE_H
