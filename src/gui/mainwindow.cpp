#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./blocks/intervalblockwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sampleLoader()
    , sampleRepository(&sampleLoader)
    , audio(new AudioProcessor(this))
    , notePlayer(new NotePlayer(audio, &sampleRepository))

{
    ui->setupUi(this);
    mainMenu = new MainMenuWidget(this);
    intervalExercise = new IntervalExerciseWidget(notePlayer, this);

    stack = ui->stackedWidget;
    stack->addWidget(mainMenu);
    stack->setCurrentWidget(mainMenu);

    blocks = {
        new IntervalBlockWidget(this)
    };

    for (auto* block : blocks) addBlock(block);

    stack->addWidget(intervalExercise);

    connect(mainMenu, &MainMenuWidget::intervalClicked,
            this, [=](){ stack->setCurrentWidget(blocks[0]); });

    connect(intervalExercise, &IntervalExerciseWidget::backClicked,
            this, [this](){
            stack->setCurrentWidget(previousWidget);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addBlock(IBlockWidget* block) {
    stack->addWidget(block);

    connect(block, &IntervalBlockWidget::backClicked,
            this, [=](){ stack->setCurrentWidget(mainMenu); });

    connect(block, &IntervalBlockWidget::exerciseSelected,
            this, &MainWindow::openExercise);

}

void MainWindow::openExercise(IBlockWidget* block, int id)
{
    previousWidget = block;
    if (id == 1) {
        stack->setCurrentWidget(intervalExercise);
    }
}

