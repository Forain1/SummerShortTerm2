#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view/menu.h"
#include "view/cast.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(new class Menu(this,":/src/bg0.jpg"));
    ui->stackedWidget->addWidget(new class Cast(this,":/src/bg0.jpg"));
    ui->stackedWidget->setCurrentIndex(CastIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}
