#ifndef CAST_H
#define CAST_H

#include <QWidget>
#include "scene.h"

namespace Ui {
class Cast;
}

class Cast : public Scene
{
    Q_OBJECT

public:
    explicit Cast(QWidget *parent = nullptr,QString path="");
    ~Cast();
signals:
    void fightBtnClicked();//进入战斗场景的信号
    void backBtnClicked();//返回主页面的信号
    void roleBtnClicked(int);//选择哪一个角色
    void setRoleBtn(bool);//控制角色按钮
public slots:
    void checkValid(int);//检测此时是否两个玩家都选择了角色
private:
    const int roleCounts = 1;//可供选择的角色有几种
    int roleChooseCount=0;
    Ui::Cast *ui;
    void reset();//点击回退或开始战斗的按钮都要让该页面重置
};

#endif // CAST_H
