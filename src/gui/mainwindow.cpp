#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainMenu = new MainMenuWidget(this);
    intervalBlock = new IntervalBlockWidget(this);

    stack = ui->stackedWidget;
    stack->addWidget(mainMenu);
    stack->addWidget(intervalBlock);
    stack->setCurrentWidget(mainMenu);

    connect(mainMenu, &MainMenuWidget::intervalClicked,
            this, [=](){ stack->setCurrentWidget(intervalBlock); });

    // connect(intervalBlock, backClicked,
    //         this, &MainWindow::showMainMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showIntervalBlock()
{
    stack->setCurrentWidget(intervalBlock);
}

void MainWindow::showMainMenu()
{
    stack->setCurrentWidget(mainMenu);
}
