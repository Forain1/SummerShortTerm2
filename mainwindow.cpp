#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view/menu.h"
#include "view/cast.h"
#include "common/index.h"
#include "view/battle.h"
#include "view/settlement.h"
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
