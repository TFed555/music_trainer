#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./blocks/intervalblockwidget.h"
#include "../core/common/interfaces/IExerciseWidget.h"
#include "../../core/sessions/intervalrecognisesession.h"

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
            this, [this](ExerciseType type, IBlockWidget* block) {
        if (session) {
            QWidget* oldView = session->getWidget();
            stack->removeWidget(oldView);
            session = nullptr;
        }
        //переделывать под фабрики
        switch(type) {
        case ExerciseType::IntervalRecognise:
            session = new IntervalRecogniseSession(
                    stack,
                    notePlayer,
                    this
                );
            exercise = session->getWidget();
            Q_ASSERT(exercise);
            qDebug() << "exercise ptr" << exercise;
            stack->addWidget(exercise);
            stack->setCurrentWidget(exercise);
            connect(session, &IntervalRecogniseSession::back,
                    this, [=]() { stack->setCurrentWidget(block); });
            break;
        case ExerciseType::IntervalBuild:

            break;
        }
    });

}


