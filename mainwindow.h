#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "controller/scenecontroller.h"
#include "view/battle.h"

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
    Battle* getBattle();
public slots:
    void SetPage(Index::PageIndex index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
