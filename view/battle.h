#ifndef BATTLE_H
#define BATTLE_H
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include"fighter.h"
#include"showhealth.h"
class Battle: public QGraphicsView
{
    Q_OBJECT
public:
    //需要传入四个参数,第二个是该场景的背景图路径,第三个和第四个是角色模型的编号,这样一来才可以加载对应角色的图示
    explicit Battle(QWidget* parent = nullptr,QString bgpath="",int role0Num=0,int role1Num=0);
    ~Battle();
    //获取角色视图
    Fighter *getFighter0(){return fighter0;}
    Fighter *getFighter1(){return fighter1;}
    //返回num指向的角色的长宽
    int getWidth(int num);
    int getHeight(int num);
signals:
    //按键按下信号
    //角色移动信号
    void pressKeyA();
    void pressKeyD();
    void pressKeyW();
    void pressKeyS();
    void pressKeyUp();
    void pressKeyDown();
    void pressKeyLeft();
    void pressKeyRight();
    //角色攻击信号
    void pressKeyAttack0();
    void pressKeyAttack1();
    //按键释放信号
    void releaseKeyA();
    void releaseKeyD();
    void releaseKeyW();
    void releaseKeyS();
    void releaseKeyUp();
    void releaseKeyDown();
    void releaseKeyLeft();
    void releaseKeyRight();
    //角色初始化信息
    void initInfo(int w0,int h0,int w1,int h1);
private:
    void loadBackground(const QString& path);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    QGraphicsScene* scene;
    QGraphicsPixmapItem* bgItem;
    Fighter* fighter0,*fighter1;
    ShowHealth *health0,*health1;

};

#endif // BATTLE_H
