#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "view/menu.h"
#include "view/cast.h"
#include "view/battle.h"
#include "view/settlement.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class SceneController;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Menu *getMenu();
    Cast *getCast();
    Battle *getBattle();
    Settlement *getSettlement();
public slots:
    void SetPage(Index::PageIndex index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
