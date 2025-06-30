#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view/menu.h"
#include "view/cast.h"
#include "common/pageindex.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(new class Menu(this,":/src/bg0.jpg"));
    ui->stackedWidget->addWidget(new class Cast(this,":/src/bg0.jpg"));
    ui->stackedWidget->setCurrentIndex(PageIndex::MenuIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetPage(PageIndex::Index index){
    ui->stackedWidget->setCurrentIndex(index);
}
