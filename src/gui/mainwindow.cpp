#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../core/common/interfaces/IExerciseWidget.h"
#include <QPushButton>

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
    // ui->setupUi(this);
    this->window()->setWindowTitle("Music trainer");

    QWidget* main = new QWidget(this);
    setCentralWidget(main);

    stack = new QStackedWidget(main);
    sidebar = new SidebarWidget(main);
    sidebar->setMaximumWidth(0);

    startMenu = new StartWidget(main);
    startMenu->setFixedSize(1000,700);

    QPushButton* menuBtn = new QPushButton("☰", main);
    connect(menuBtn, &QPushButton::clicked, sidebar, &SidebarWidget::open);

    stack->addWidget(startMenu);
    stack->setCurrentWidget(startMenu);

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(menuBtn, 0, Qt::AlignLeft);
    leftLayout->addWidget(stack);

    QHBoxLayout* mainLayout = new QHBoxLayout(main);
    mainLayout->addWidget(sidebar);
    mainLayout->addLayout(leftLayout);

    connect(sidebar, &SidebarWidget::blockSelected,
            startMenu, &StartWidget::setBlock);
    connect(sidebar, &SidebarWidget::blockSelected,
            this, [this]() {
            stack->setCurrentWidget(startMenu);
            this->window()->setWindowTitle("Music trainer");
        });
    connect(startMenu, &StartWidget::exerciseSelected,
            this, &MainWindow::startExercise);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startExercise(ExerciseType type){
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

    exercise = session->getWidget();
    exercise->setParent(stack);
    this->setWindowTitle(session->title());

    disconnect(sessionBackConn);

    sessionBackConn = connect(session.get(), &ISession::back,
                              this, [=]() {
        stack->setCurrentWidget(startMenu);
        this->setWindowTitle(mainTitle);  });

    // sidebar->open();

    stack->addWidget(exercise);
    stack->setCurrentWidget(exercise);
}
