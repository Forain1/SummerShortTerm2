#include "scenecontroller.h"
#include "../mainwindow.h"
#include "../view/menu.h"
#include "../model/scenestate.h"

SceneController::SceneController(MainWindow *mainWindow,QObject *parent)
    : mainWindow{mainWindow},QObject{parent}
{
    sceneState=new SceneState;
    QWidget* menuWidget=mainWindow->ui->stackedWidget->widget(0);
    if(Menu *menu=qobject_cast<Menu *>(menuWidget)){
        connect(menu,&Menu::startBtnClicked,this,[=](){emit turnToPage(PageIndex::CastIndex);});
        connect(this,&SceneController::turnToPage,sceneState,&SceneState::setCurrentPageIndex);
        connect(sceneState,&SceneState::currentPageIndexChanged,mainWindow,&MainWindow::SetPage);
    }
}
