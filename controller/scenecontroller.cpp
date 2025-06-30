#include "scenecontroller.h"
#include "../mainwindow.h"
#include "../view/menu.h"
#include "../view/cast.h"
#include "../view/battle.h"
#include "../view/settlement.h"
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
    QWidget* castWidget=mainWindow->ui->stackedWidget->widget(1);
    if(Cast *cast=qobject_cast<Cast *>(castWidget)){
        connect(cast,&Cast::backBtnClicked,this,[=](){emit turnToPage(Index::MenuIndex);});
        connect(cast,&Cast::fightBtnClicked,this,[=](){emit turnToPage(Index::BattleIndex);});
    }
    // QWidget* battleWidget=mainWindow->ui->stackedWidget->widget(2);
    // if(Battle *battle=qobject_cast<Battle *>(castWidget)){
    //     connect(battle,&Battle,this,[=](){emit turnToPage(Index::MenuIndex);});
    // }
    QWidget* settlementWidget=mainWindow->ui->stackedWidget->widget(3);
    if(Settlement *settlement=qobject_cast<Settlement *>(settlementWidget)){
        connect(settlement,&Settlement::onceMoreBtnClicked,this,[=](){emit turnToPage(Index::BattleIndex);});
        connect(settlement,&Settlement::returnMenuBtnClicked,this,[=](){emit turnToPage(Index::MenuIndex);});
    }

    //controller->model,model->view
    connect(this,&SceneController::turnToPage,sceneState,&SceneState::setCurrentPageIndex);
    connect(sceneState,&SceneState::currentPageIndexChanged,mainWindow,&MainWindow::SetPage);
}
