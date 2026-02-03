#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainMenu = new MainMenuWidget(this);
    intervalBlock = new IntervalBlockWidget(this);
    intervalExercise = new IntervalExerciseWidget(this);

    stack = ui->stackedWidget;
    stack->addWidget(mainMenu);
    stack->addWidget(intervalBlock);
    stack->setCurrentWidget(mainMenu);
    stack->addWidget(intervalExercise);

    connect(mainMenu, &MainMenuWidget::intervalClicked,
            this, [=](){ stack->setCurrentWidget(intervalBlock); });

    connect(intervalBlock, &IntervalBlockWidget::backClicked,
            this, [=](){ stack->setCurrentWidget(mainMenu); });

    connect(intervalBlock, &IntervalBlockWidget::exerciseSelected,
            this, &MainWindow::openIntervalExercise);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openIntervalExercise(int id)
{
    if (id == 1) {
        stack->setCurrentWidget(intervalExercise);
    }
}
