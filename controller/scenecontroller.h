#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QObject>
#include "../common/pageindex.h"
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
    void turnToPage(PageIndex::Index index);
};

#endif // SCENECONTROLLER_H
