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
    void FightBtnClicked();//进入战斗场景的信号
    void BackBtnClicked();//返回主页面的信号
    void RoleBtnClicked(int);//选择哪一个角色
private:
    const int roleCounts = 1;//可供选择的角色有几种
    Ui::Cast *ui;
};

#endif // CAST_H
