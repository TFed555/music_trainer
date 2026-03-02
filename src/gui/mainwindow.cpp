#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./blocks/intervalblockwidget.h"
#include "../core/common/interfaces/IExerciseWidget.h"
#include "../../core/sessions/intervalrecognisesession.h"
#include "../../core/sessions/intervalidentifysession.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sampleLoader()
    , sampleRepository(&sampleLoader)
    , audio(new AudioProcessor(this))
    , notePlayer(new NotePlayer(audio, &sampleRepository))
    , session(nullptr)
{
    ui->setupUi(this);
    mainMenu = new MainMenuWidget(this);
    mainMenu->setFixedSize(800,800);
    this->window()->setWindowTitle("Music trainer");
    stack = ui->stackedWidget;
    stack->addWidget(mainMenu);
    stack->setCurrentWidget(mainMenu);

    // QVBoxLayout *layout = new QVBoxLayout();
    // // layout->addStrut(200);
    // layout->addWidget(stack);
    // setLayout(layout);
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
    block->setFixedSize(800,800);
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
            session = new IntervalRecogniseSession(stack, notePlayer, this);
            exercise = session->getWidget();
            this->setWindowTitle("Exercise 1");
            connect(exercise, &ExerciseWithTilesWidget::backClicked,
                    this, [this]() {
                    this->setWindowTitle("Music trainer");
                });

            stack->addWidget(exercise);
            stack->setCurrentWidget(exercise);
            connect(session, &IntervalRecogniseSession::back,
                    this, [=]() { stack->setCurrentWidget(block); });
            break;
        case ExerciseType::IntervalIdentify:
            session = new IntervalIdentifySession(stack, notePlayer, this);
            exercise = session->getWidget();
            this->setWindowTitle("Exercise 2");
            connect(exercise, &ExerciseWithTilesWidget::backClicked,
                    this, [this]() {
                        this->setWindowTitle("Music trainer");
                    });

            exercise->setFixedSize(1000,1000);
            stack->addWidget(exercise);
            stack->setCurrentWidget(exercise);
            connect(session, &IntervalRecogniseSession::back,
                    this, [=]() { stack->setCurrentWidget(block); });
            break;
        }
    });

}


