#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./blocks/intervalblockwidget.h"
#include "./blocks/chordblockwidget.h"
#include "../core/common/interfaces/IExerciseWidget.h"

MainWindow::MainWindow(SessionFactory& factory, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sampleLoader()
    , sampleRepository(&sampleLoader)
    , audio(new AudioProcessor(this))
    , notePlayer(new NotePlayer(audio, &sampleRepository))
    , session(nullptr)
    , sessionFactory(factory)
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

    QMap<IBlockWidget::BlockCategory, IBlockWidget*> blockNames = {
        {IBlockWidget::BlockCategory::Intervals, blocks[0]},
        {IBlockWidget::BlockCategory::Chords, blocks[1]}
    };

    for (auto* block : blocks) addBlock(block);

    connect(mainMenu, &MainMenuWidget::intervalClicked,
            this, [=](){ stack->setCurrentWidget(blockNames[IBlockWidget::BlockCategory::Intervals]); });

    connect(mainMenu, &MainMenuWidget::chordClicked,
            this, [=](){ stack->setCurrentWidget(blockNames[IBlockWidget::BlockCategory::Chords]); });
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
            IExerciseWidget* oldView = session->getWidget();
            if (oldView) {
                stack->removeWidget(oldView);
            }
            session.reset();
        }

        auto newSession = sessionFactory.create(type, notePlayer, this);
        if (!newSession) return;
        session.reset(newSession.release());
        addExercise(block, "");
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

    sessionBackConn = connect(session.get(), &ISession::back,
                              this, [=]() { stack->setCurrentWidget(block); });

    stack->addWidget(exercise);
    stack->setCurrentWidget(exercise);
}
