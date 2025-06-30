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
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1600,900);
    ui->stackedWidget->addWidget(new  Menu(this,":/src/bg0.jpg"));
    ui->stackedWidget->addWidget(new  Cast(this,":/src/bg0.jpg"));
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
}

Battle *MainWindow::getBattle(){
    return qobject_cast<Battle*>(ui->stackedWidget->widget(Index::BattleIndex));
}
