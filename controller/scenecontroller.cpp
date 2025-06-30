#include "scenecontroller.h"
#include "../mainwindow.h"
#include "../view/menu.h"
#include "../view/cast.h"
#include "../view/battle.h"
#include "../model/scenestate.h"

SceneController::SceneController(MainWindow *mainWindow,QObject *parent)
    : mainWindow{mainWindow},QObject{parent}
{
    sceneState=new SceneState;
    //跳转相关Btn信号连接,view->controller
    QWidget* menuWidget=mainWindow->ui->stackedWidget->widget(0);
    if(Menu *menu=qobject_cast<Menu *>(menuWidget)){
        connect(menu,&Menu::startBtnClicked,this,[=](){emit turnToPage(Index::CastIndex);});
    }
    // QWidget* castWidget=mainWindow->ui->stackedWidget->widget(1);
    // if(Cast *cast=qobject_cast<Cast *>(castWidget)){
    //     connenct(cast,&Cast::,this,[=](){emit turnToPage(Index::MenuIndex);});
    // }
    // QWidget* battleWidget=mainWindow->ui->stackedWidget->widget(2);
    // if(Battle *battle=qobject_cast<Battle *>(castWidget)){
    //     connenct(battle,&Battle::,this,[=](){emit turnToPage(Index::MenuIndex);});
    // }

    //controller->model,model->view
    connect(this,&SceneController::turnToPage,sceneState,&SceneState::setCurrentPageIndex);
    connect(sceneState,&SceneState::currentPageIndexChanged,mainWindow,&MainWindow::SetPage);
}
