#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "scene.h"
namespace Ui {
class Menu;
}

class Menu : public Scene
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr,QString path="");
    ~Menu();
public slots:
    void showAbout();
private:
    Ui::Menu *ui;
signals:
    void startBtnClicked();
};

#endif // MENU_H
