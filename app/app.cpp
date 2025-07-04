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
    timer->setInterval(50);
    
    // 连接timer到TopModel的nextFrame，但不启动
    connect(timer,&QTimer::timeout,viewModel,&TopModel::nextFrame);

    setSceneConnection();

    view->show();
}

void App::setSceneConnection(){
    //在按下fightBtn后，battle层发送角色model相关info信号
    connect(view->getCast(),&Cast::fightBtnClicked,view->getBattle(),[=](){
        Battle *battle=view->getBattle();
        emit battle->initInfo(battle->getWidth(0),battle->getHeight(0),battle->getWidth(1),battle->getHeight(1));
    });
    //info信号被model接收，model创建角色实例
    connect(view->getBattle(),&Battle::initInfo,viewModel,[=](int w0,int h0,int w1,int h1){
        viewModel->getInfo(w0,h0,w1,h1);
        setCharacterConnection();
        fightStart();
    });

    //连接view的各种btn和sceneState model
    connect(view->getMenu(),&Menu::startBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::CastIndex);});
    connect(view->getCast(),&Cast::backBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::MenuIndex);});
    connect(view->getCast(),&Cast::fightBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::BattleIndex);});
    connect(view->getSettlement(),&Settlement::onceMoreBtnClicked,viewModel->getSceneState(),[=](){
        //onceMore时,启动计时器
        this->fightStart();
        viewModel->getSceneState()->turnToPage(Index::BattleIndex);
    });

    //返回主菜单
    connect(view->getSettlement(),&Settlement::returnMenuBtnClicked,viewModel->getSceneState(),[=](){viewModel->getSceneState()->turnToPage(Index::MenuIndex);});

    //connect sceneStateModel的变化->view层的变化
    connect(viewModel->getSceneState(),&SceneState::currentPageIndexChanged,view,&MainWindow::SetPage);

    //血量归0，游戏结束
    connect(viewModel,&TopModel::gameOver,this,&App::fightEnd);
    //esc，游戏暂停，esc结束，游戏继续
    connect(view,&MainWindow::pressEsc,this,&App::fightStop);
    connect(view,&MainWindow::escToMenu,this,[=](){viewModel->getSceneState()->turnToPage(Index::MenuIndex);});
    connect(view,&MainWindow::rejectEsc,this,&App::fightContinue);
}


void App::setCharacterConnection(){
    //character model刷新完毕，更新view
    connect(viewModel->getCharacter0(),&Character::frameUpdate,view->getBattle()->getFighter0(),&Fighter::nextFrame);
    connect(viewModel->getCharacter1(),&Character::frameUpdate,view->getBattle()->getFighter1(),&Fighter::nextFrame);

    //连接按键信号和character model槽函数
    connect(view->getBattle(),&Battle::pressKeyA,viewModel->getCharacter0(),&Character::handleLeftMove);
    connect(view->getBattle(),&Battle::pressKeyD,viewModel->getCharacter0(),&Character::handleRightMove);
    connect(view->getBattle(),&Battle::pressKeyW,viewModel->getCharacter0(),&Character::handleJump);
    connect(view->getBattle(),&Battle::pressKeyS,viewModel->getCharacter0(),&Character::handleDefend);
    connect(view->getBattle(),&Battle::pressKeyAttack0,viewModel->getCharacter0(),&Character::handleAttack);

    connect(view->getBattle(),&Battle::pressKeyLeft,viewModel->getCharacter1(),&Character::handleLeftMove);
    connect(view->getBattle(),&Battle::pressKeyRight,viewModel->getCharacter1(),&Character::handleRightMove);
    connect(view->getBattle(),&Battle::pressKeyUp,viewModel->getCharacter1(),&Character::handleJump);
    connect(view->getBattle(),&Battle::pressKeyDown,viewModel->getCharacter1(),&Character::handleDefend);
    connect(view->getBattle(),&Battle::pressKeyAttack1,viewModel->getCharacter1(),&Character::handleAttack);

    connect(view->getBattle(),&Battle::releaseKeyA,viewModel->getCharacter0(),&Character::handleStopLeftMove);
    connect(view->getBattle(),&Battle::releaseKeyD,viewModel->getCharacter0(),&Character::handleStopRightMove);
    connect(view->getBattle(),&Battle::releaseKeyS,viewModel->getCharacter0(),&Character::handleStopDefend);
    connect(view->getBattle(),&Battle::releaseKeyLeft,viewModel->getCharacter1(),&Character::handleStopLeftMove);
    connect(view->getBattle(),&Battle::releaseKeyRight,viewModel->getCharacter1(),&Character::handleStopRightMove);
    connect(view->getBattle(),&Battle::releaseKeyDown,viewModel->getCharacter1(),&Character::handleStopDefend);
    //连接血量变化信号和view层血槽显示
    connect(viewModel->getCharacter0(),&Character::healthUpdate,view->getBattle()->getHealth0(),&ShowHealth::changeHealth);
    connect(viewModel->getCharacter1(),&Character::healthUpdate,view->getBattle()->getHealth1(),&ShowHealth::changeHealth);
}

void App::fightStart(){
    // 重置角色
    viewModel->initCharacter();
    // 启动timer
    timer->start();
}

void App::fightEnd(){
    timer->stop();
    viewModel->getSceneState()->turnToPage(Index::SettlementIndex);
}

void App::fightStop(){
    timer->stop();
}

void App::fightContinue(){
    timer->start();
}
