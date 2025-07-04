#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "view/menu.h"
#include "view/cast.h"
#include "view/battle.h"
#include "view/settlement.h"
#include "view/esc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
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
    void finishEsc(int);
signals:
    void pressEsc();
    void rejectEsc();
    void escToMenu();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    Ui::Game *ui;
    Esc* esc;
};
#endif // MAINWINDOW_H
