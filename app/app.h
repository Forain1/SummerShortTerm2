#ifndef APP_H
#define APP_H

#include <QObject>
#include <QTimer>

class MainWindow;
class Character;
class SceneState;
class SceneController;

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);
private:
    QTimer *timer;

    MainWindow *view;
    Character *c0;
    Character *c1;

    SceneState *sceneState;
    SceneController *sceneController;

    void setConnection();
};

#endif // APP_H
