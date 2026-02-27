#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./blocks/intervalblockwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    // , sampleLoader()
    // , sampleRepository(&sampleLoader)
    // , audio(new AudioProcessor(this))
    // , notePlayer(new NotePlayer(audio, &sampleRepository))

{
    ui->setupUi(this);
    mainMenu = new MainMenuWidget(this);

    stack = ui->stackedWidget;
    stack->addWidget(mainMenu);
    stack->setCurrentWidget(mainMenu);

    blocks = {
        new IntervalBlockWidget(this)
    };

    for (auto* block : blocks) addBlock(block);

    connect(mainMenu, &MainMenuWidget::intervalClicked,
            this, [=](){ stack->setCurrentWidget(blocks[0]); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addBlock(IBlockWidget* block) {
    stack->addWidget(block);

    connect(block, &IBlockWidget::backClicked,
            this, [=](){ stack->setCurrentWidget(mainMenu); });

    connect(block, &IBlockWidget::exerciseSelected,
            this, [this](QWidget* exercise) {
        stack->setCurrentWidget(exercise);
    });

    connect(block, &IBlockWidget::exerciseBackClicked,
            this, [=]() { stack->setCurrentWidget(block); });
}


