#include "exercisewithtileswidget.h"
#include "ui_exercisewithtileswidget.h"
// #include <QEventLoop>
#include <QTimer>
#include <QLabel>

ExerciseWithTilesWidget::ExerciseWithTilesWidget(QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::ExerciseWithTilesWidget)
    , tiles(new NoteTilesWidget(this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(tiles);

    connect(ui->startBtn, &QPushButton::clicked, this, [this] {
            emit startClicked();
            setMode(Mode::Wait);
        });
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::backClicked);
    connect(tiles, &NoteTilesWidget::noteSelected, this, &ExerciseWithTilesWidget::noteSelected);
    connect(this, &ExerciseWithTilesWidget::requestSetMode,
        this, &ExerciseWithTilesWidget::setMode);
}

ExerciseWithTilesWidget::~ExerciseWithTilesWidget()
{
    delete ui;
}

void ExerciseWithTilesWidget::exercisePlayFinished() {
    emit requestSetMode(Mode::Input);
}

void ExerciseWithTilesWidget::showResult(const QVector<QString>& correct) {
    tiles->highlight(correct);
    QTimer::singleShot(2000, this, [this]() {
        emit requestSetMode(Mode::Wait); //временно
    });
}

void ExerciseWithTilesWidget::setMode(Mode m) {
    tiles->setMode(m);
}

void ExerciseWithTilesWidget::setQuestion(const QString& question) {
    QLabel* questionLabel = new QLabel(question, this);
    ui->manageLayout->addWidget(questionLabel);
}

void ExerciseWithTilesWidget::highlightQuestion(QVector<QString> notes) {
    tiles->highlight(notes);
}
