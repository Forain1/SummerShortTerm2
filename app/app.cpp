#include "app.h"

#include "../mainwindow.h"
#include "../model/character.h"
#include "../model/scenestate.h"
#include "../common/index.h"

App::App(QObject *parent)
    : QObject{parent}
{
    view=new MainWindow();
    //创建角色
    c0 = new Character(20,BATTLEHEIGHT-view->getBattle()->getHeight(0),Index::rightIndex,this);
    c1 = new Character(BATTLEWIDTH-20-view->getBattle()->getWidth(1),BATTLEHEIGHT-view->getBattle()->getHeight(1),Index::leftIndex,this);

    timer=new QTimer(this);
    timer->setInterval(100);
    timer->start();

    sceneState=new SceneState(this);

    setConnection();

    view->show();
}

void App::setConnection(){
    //通知character model更新
    connect(timer,&QTimer::timeout,c0,&Character::nextFrame);
    connect(timer,&QTimer::timeout,c1,&Character::nextFrame);
    //character model更新完毕，更新view
    connect(c0,&Character::frameUpdate,view->getBattle()->getFighter0(),&Fighter::nextFrame);
    connect(c1,&Character::frameUpdate,view->getBattle()->getFighter1(),&Fighter::nextFrame);

    //连接按键信号和character model槽函数
    connect(view->getBattle(),&Battle::pressKeyA,c0,&Character::handlePressKeyA);
    connect(view->getBattle(),&Battle::pressKeyD,c0,&Character::handlePressKeyD);
    connect(view->getBattle(),&Battle::pressKeyW,c0,&Character::handlePressKeyW);
    connect(view->getBattle(),&Battle::pressKeyS,c0,&Character::handlePressKeyS);
    connect(view->getBattle(),&Battle::pressKeyLeft,c1,&Character::handlePressKeyLeft);
    connect(view->getBattle(),&Battle::pressKeyRight,c1,&Character::handlePressKeyRight);
    connect(view->getBattle(),&Battle::pressKeyUp,c1,&Character::handlePressKeyUp);
    connect(view->getBattle(),&Battle::pressKeyDown,c1,&Character::handlePressKeyDown);

    connect(view->getBattle(),&Battle::releaseKeyA,c0,&Character::handleReleaseKeyA);
    connect(view->getBattle(),&Battle::releaseKeyD,c0,&Character::handleReleaseKeyD);
    connect(view->getBattle(),&Battle::releaseKeyS,c0,&Character::handleReleaseKeyS);
    connect(view->getBattle(),&Battle::releaseKeyLeft,c1,&Character::handleReleaseKeyLeft);
    connect(view->getBattle(),&Battle::releaseKeyRight,c1,&Character::handleReleaseKeyRight);
    connect(view->getBattle(),&Battle::releaseKeyDown,c1,&Character::handleReleaseKeyDown);

    //连接view的各种btn和sceneState model
    connect(view->getMenu(),&Menu::startBtnClicked,sceneState,[=](){sceneState->turnToPage(Index::CastIndex);});
    connect(view->getCast(),&Cast::backBtnClicked,sceneState,[=](){sceneState->turnToPage(Index::MenuIndex);});
    connect(view->getCast(),&Cast::fightBtnClicked,sceneState,[=](){sceneState->turnToPage(Index::BattleIndex);});
    connect(view->getSettlement(),&Settlement::onceMoreBtnClicked,sceneState,[=](){sceneState->turnToPage(Index::BattleIndex);});
    connect(view->getSettlement(),&Settlement::returnMenuBtnClicked,sceneState,[=](){sceneState->turnToPage(Index::MenuIndex);});
    //connect sceneState的model变化->view层的变化
    connect(sceneState,&SceneState::currentPageIndexChanged,view,&MainWindow::SetPage);
}
