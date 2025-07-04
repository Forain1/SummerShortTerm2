#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view/menu.h"
#include "view/cast.h"
#include "common/index.h"
#include "view/battle.h"
#include "view/settlement.h"
#include "view/esc.h"
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    setFixedSize(1600,900);
    ui->stackedWidget->addWidget(new  Menu(this,":/src/bg0.jpg"));
    ui->stackedWidget->addWidget(new  Cast(this,":/src/bg0.jpg"));
    //Battle需要额外添加一个布局让他撑满整个页面
    ui->stackedWidget->addWidget(new  Battle(this,":/src/bg0.jpg"));
    ui->stackedWidget->addWidget(new Settlement(this));
    ui->stackedWidget->setCurrentIndex(Index::MenuIndex);

    //初始化事件过滤器,这里需要过滤出esc键,使得在全局可以使用
    ui->stackedWidget->widget(Index::MenuIndex)->installEventFilter(this);
    ui->stackedWidget->widget(Index::CastIndex)->installEventFilter(this);
    ui->stackedWidget->widget(Index::BattleIndex)->installEventFilter(this);

    //连接esc
    esc=new Esc(this);
    connect(esc,&Esc::volumeChange,getBattle(),&Battle::volumeChange);
    connect(esc,&Esc::rejected,this,&MainWindow::rejectEsc);
    connect(esc,&Esc::pressMenu,this,&MainWindow::escToMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::SetPage(Index::PageIndex index){
    ui->stackedWidget->setCurrentIndex(index);
    ui->stackedWidget->currentWidget()->setFocus();
    qDebug() << "Focus now on:" << QApplication::focusWidget();
    if(index==Index::BattleIndex){
        getBattle()->loadMusic();
    }
}

Menu *MainWindow::getMenu(){
    return qobject_cast<Menu *>(ui->stackedWidget->widget(Index::MenuIndex));
}

Cast *MainWindow::getCast(){
    return qobject_cast<Cast *>(ui->stackedWidget->widget(Index::CastIndex));
}

Battle *MainWindow::getBattle(){
    return qobject_cast<Battle *>(ui->stackedWidget->widget(Index::BattleIndex));
}


Settlement *MainWindow::getSettlement(){
    return qobject_cast<Settlement *>(ui->stackedWidget->widget(Index::SettlementIndex));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if(event->type()==QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(!keyEvent->isAutoRepeat()&&keyEvent->key()==Qt::Key_Escape){
            emit pressEsc();
            esc->exec();
            qDebug()<<"esc";
            return true;
        }
    }
    return QObject::eventFilter(obj,event);
}
