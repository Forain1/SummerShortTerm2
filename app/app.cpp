#include "app.h"

#include "../mainwindow.h"
#include "../model/topmodel.h"
#include "../model/character.h"
#include "../model/scenestate.h"
#include "../common/index.h"

App::App(QObject *parent)
    : QObject{parent}
{
    view=new MainWindow();

    viewModel=new TopModel();

    timer=new QTimer(this);
    timer->setInterval(100);
    timer->start();

    setConnection();

    view->show();
}

void App::setConnection(){
    //view告知model角色的宽度和长度
    connect(view->getBattle(),&Battle::initInfo,viewModel,&TopModel::getSize);
    //通知character model更新
    connect(timer,&QTimer::timeout,viewModel->getCharacter0(),&Character::nextFrame);
    connect(timer,&QTimer::timeout,viewModel->getCharacter1(),&Character::nextFrame);
    //character model更新完毕，更新view
    connect(viewModel->getCharacter0(),&Character::frameUpdate,view->getBattle()->getFighter0(),&Fighter::nextFrame);
    connect(viewModel->getCharacter1(),&Character::frameUpdate,view->getBattle()->getFighter1(),&Fighter::nextFrame);

    //连接按键信号和character model槽函数
    connect(view->getBattle(),&Battle::pressKeyA,viewModel->getCharacter0(),&Character::handlePressKeyA);
    connect(view->getBattle(),&Battle::pressKeyD,viewModel->getCharacter0(),&Character::handlePressKeyD);
    connect(view->getBattle(),&Battle::pressKeyW,viewModel->getCharacter0(),&Character::handlePressKeyW);
    connect(view->getBattle(),&Battle::pressKeyS,viewModel->getCharacter0(),&Character::handlePressKeyS);
    connect(view->getBattle(),&Battle::pressKeyLeft,viewModel->getCharacter1(),&Character::handlePressKeyLeft);
    connect(view->getBattle(),&Battle::pressKeyRight,viewModel->getCharacter1(),&Character::handlePressKeyRight);
    connect(view->getBattle(),&Battle::pressKeyUp,viewModel->getCharacter1(),&Character::handlePressKeyUp);
    connect(view->getBattle(),&Battle::pressKeyDown,viewModel->getCharacter1(),&Character::handlePressKeyDown);

    connect(view->getBattle(),&Battle::releaseKeyA,viewModel->getCharacter0(),&Character::handleReleaseKeyA);
    connect(view->getBattle(),&Battle::releaseKeyD,viewModel->getCharacter0(),&Character::handleReleaseKeyD);
    connect(view->getBattle(),&Battle::releaseKeyS,viewModel->getCharacter0(),&Character::handleReleaseKeyS);
    connect(view->getBattle(),&Battle::releaseKeyLeft,viewModel->getCharacter1(),&Character::handleReleaseKeyLeft);
    connect(view->getBattle(),&Battle::releaseKeyRight,viewModel->getCharacter1(),&Character::handleReleaseKeyRight);
    connect(view->getBattle(),&Battle::releaseKeyDown,viewModel->getCharacter1(),&Character::handleReleaseKeyDown);

    //连接view的各种btn和sceneState model
    connect(view->getMenu(),&Menu::startBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::CastIndex);});
    connect(view->getCast(),&Cast::backBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::MenuIndex);});
    connect(view->getCast(),&Cast::fightBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::BattleIndex);});
    connect(view->getSettlement(),&Settlement::onceMoreBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::BattleIndex);});
    connect(view->getSettlement(),&Settlement::returnMenuBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::MenuIndex);});
    //connect sceneState的model变化->view层的变化
    connect(viewModel->getSceneState(),&SceneState::currentPageIndexChanged,view,&MainWindow::SetPage);
}
