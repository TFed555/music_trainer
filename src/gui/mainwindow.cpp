#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./blocks/intervalblockwidget.h"
#include "./blocks/chordblockwidget.h"
#include "../core/common/interfaces/IExerciseWidget.h"
#include "../../core/sessions/intervals/intervalrecognisesession.h"
#include "../../core/sessions/intervals/intervalidentifysession.h"
#include "../../core/sessions/intervals/intervalbuildsession.h"
#include "../../core/sessions/intervals/intervaldirectionsession.h"
#include "../../core/sessions/chords/chordidentifysession.h"
#include "../../core/sessions/chords/chordinversionsession.h"

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
        new IntervalBlockWidget(this),
        new ChordBlockWidget(this)
    };

    for (auto* block : blocks) addBlock(block);

    connect(mainMenu, &MainMenuWidget::intervalClicked,
            this, [=](){ stack->setCurrentWidget(blocks[0]); });

    connect(mainMenu, &MainMenuWidget::chordClicked,
            this, [=](){ stack->setCurrentWidget(blocks[1]); });
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
            if (oldView) {
                stack->removeWidget(oldView);
                delete oldView;
            }
            delete session;
            session = nullptr;
        }

        switch(type) {
        case ExerciseType::IntervalRecognise:
            session = new IntervalRecogniseSession(notePlayer, this);
            addExercise(block, "Exercise 1");
            break;
        case ExerciseType::IntervalIdentify:
            session = new IntervalIdentifySession(notePlayer, this);
            addExercise(block, "Exercise 2");
            break;
        case ExerciseType::IntervalBuild:
            session = new IntervalBuildSession(notePlayer, this);
            addExercise(block, "Exercise 3");
            break;
        case ExerciseType::IntervalDirection:
            session = new IntervalDirectionSession(notePlayer, this);
            addExercise(block, "Exercise 4");
            break;
        case ExerciseType::ChordIdentify:
            session = new ChordIdentifySession(notePlayer, this);
            addExercise(block, "Exercise 1");
            break;
        case ExerciseType::ChordInversion:
            session = new ChordInversionSession(notePlayer, this);
            addExercise(block, "Exercise 2");
            break;
        }
    });
}

void MainWindow::addExercise(IBlockWidget* block, QString title) {
    exercise = session->getWidget();
    exercise->setParent(stack);
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
