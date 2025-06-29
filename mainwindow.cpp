#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view/menu.h"
#include "view/cast.h"
#include "view/battle.h"
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
    ui->stackedWidget->setCurrentIndex(BattleIndex);

}

MainWindow::~MainWindow()
{
    delete ui;
}


