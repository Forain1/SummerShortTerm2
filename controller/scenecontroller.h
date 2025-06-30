#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QObject>
#include "../common/index.h"
#include "../model/scenestate.h"

class MainWindow;

class SceneController : public QObject
{
    Q_OBJECT
public:
    explicit SceneController(MainWindow *mainWindow,QObject *parent = nullptr);
    void ShowMenu(){
    }
private:
    MainWindow *mainWindow;
    SceneState *sceneState;
signals:
    void turnToPage(Index::PageIndex index);
};

#endif // SCENECONTROLLER_H
