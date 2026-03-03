#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./blocks/intervalblockwidget.h"
#include "../core/common/interfaces/IExerciseWidget.h"
#include "../../core/sessions/intervalrecognisesession.h"
#include "../../core/sessions/intervalidentifysession.h"
#include "../../core/sessions/intervalbuildsession.h"

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
            oldView->setParent(nullptr);
            // delete oldView;
            delete session;
            session = nullptr;
        }

        switch(type) {
        case ExerciseType::IntervalRecognise:
            session = new IntervalRecogniseSession(stack, notePlayer, this);
            addExercise(block, "Exercise 1");
            break;
        case ExerciseType::IntervalIdentify:
            session = new IntervalIdentifySession(stack, notePlayer, this);
            addExercise(block, "Exercise 2");
            break;
        case ExerciseType::IntervalBuild:
            session = new IntervalBuildSession(stack, notePlayer, this);
            addExercise(block, "Exercise 3");
            break;
        }
    });
}

void MainWindow::addExercise(IBlockWidget* block, QString title) {
    exercise = session->getWidget();
    this->setWindowTitle(title);

    disconnect(sessionBackConn);
    disconnect(exerciseBackConn);

    exerciseBackConn = connect(exercise, &IExerciseWidget::backClicked,
                               this, [this]() {
                                   this->setWindowTitle(mainTitle);
                               });

    sessionBackConn = connect(session, &ISession::back,
                              this, [=]() { stack->setCurrentWidget(block); });

    stack->addWidget(exercise);
    stack->setCurrentWidget(exercise);
}
