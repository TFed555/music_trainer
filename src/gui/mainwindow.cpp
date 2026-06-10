#include "mainwindow.h"
#include "../core/common/interfaces/IExerciseWidget.h"
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(SessionFactory& factory, QWidget *parent)
    : QMainWindow(parent)
    , sampleLoader()
    , sampleRepository(&sampleLoader)
    , audio(new AudioProcessor(this))
    , notePlayer(new NotePlayer(audio, &sampleRepository))
    , session(nullptr)
    , statsLoader()
    , statsRepository(&statsLoader)
    , sessionFactory(factory)
{
    this->window()->setWindowTitle("Music Trainer");
    this->window()->setFixedSize(1150,800);

    QWidget* main = new QWidget(this);
    setCentralWidget(main);

    stack = new QStackedWidget(main);
    sidebar = new SidebarWidget(main);
    stats = new StatsWidget(&statsRepository, main);
    sidebar->setMaximumWidth(0);

    startMenu = new StartWidget(main);
    startMenu->setFixedSize(1000,700);

    QPushButton* menuBtn = new QPushButton("☰", main);
    menuBtn->setObjectName("menuBtn");
    connect(menuBtn, &QPushButton::clicked, sidebar, &SidebarWidget::toggle);

    stack->addWidget(startMenu);
    stack->addWidget(stats);
    stack->setCurrentWidget(startMenu);

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(menuBtn, 0, Qt::AlignLeft);
    leftLayout->addWidget(stack);

    QHBoxLayout* mainLayout = new QHBoxLayout(main);
    mainLayout->addWidget(sidebar);
    mainLayout->addLayout(leftLayout);

    QMenuBar* menu = menuBar();

    settingsMenu = menu->addMenu(tr("Настройки"));
    helpMenu = menu->addMenu(tr("Помощь"));
    langMenu = settingsMenu->addMenu(tr("Язык"));
    langMenu->addAction("Русский", this, [this]() { setLanguage("ru"); });
    langMenu->addAction("English",  this, [this]() { setLanguage("en"); });
    instructionAction = helpMenu->addAction(tr("Как пользоваться"), this, [this]() { showInstruction();});
    aboutAction = helpMenu->addAction(tr("О программе"), this, [this]() { showAbout(); });

    statsAction = settingsMenu->addAction(tr("Статистика"));
    exitAction  = settingsMenu->addAction(tr("Выход"));

    connect(statsAction, &QAction::triggered, this, &MainWindow::showStats);
    connect(exitAction,  &QAction::triggered, this, &QApplication::quit);

    connect(sidebar, &SidebarWidget::blockSelected,
            startMenu, &StartWidget::setBlock);
    connect(sidebar, &SidebarWidget::blockSelected,
            this, [this]() {
            stack->setCurrentWidget(startMenu);
            this->window()->setWindowTitle("Music Trainer");
        });
    connect(startMenu, &StartWidget::exerciseSelected,
            this, &MainWindow::startExercise);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showInstruction() {
    QMessageBox::information(this, tr("Как пользоваться"),
            tr("1. Выберите категорию упражнений в меню слева\n"
                "2. Нажмите на нужное упражнение\n"
                "3. Прослушайте задание\n"
                "4. Выберите правильный ответ\n"
                "5. После ввода отобразится результат"),
                QMessageBox::Ok);
}

void MainWindow::showAbout() {
    QMessageBox::information(this, tr("О программе"),
                             tr("Music Trainer\n"
                                "Версия 1.0\n"
                                "Приложение для развития музыкального слуха\n"
                                "Разработано с использованием Qt Framework"),
                             QMessageBox::Ok);
}

void MainWindow::setLanguage(const QString& lang) {
    bool f = translator.load(QString(":/translation/app_%1").arg(lang));
    qApp->installTranslator(&translator);
    update();
}

void MainWindow::showStats() {
    stack->setCurrentWidget(stats);
}

void MainWindow::startExercise(ExerciseType type){
    if (session) {
        IExerciseWidget* oldView = session->getWidget();
        if (oldView) {
            stack->removeWidget(oldView);
        }
        session.reset();
    }
    auto newSession = sessionFactory.create(type, notePlayer, &statsRepository, this);
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

    sidebar->close();

    stack->addWidget(exercise);
    stack->setCurrentWidget(exercise);
}

void MainWindow::changeEvent(QEvent* event) {
    if (event->type() == QEvent::LanguageChange) {
        qDebug() << "changeEvent" << event->type();
        retranslateUi();
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::retranslateUi() {
    settingsMenu->setTitle(tr("Настройки"));
    helpMenu->setTitle(tr("Помощь"));
    langMenu->setTitle(tr("Язык"));
    exitAction->setText(tr("Выход"));
    statsAction->setText(tr("Статистика"));
    instructionAction->setText(tr("Как пользоваться"));
    aboutAction->setText(tr("О программе"));
}
