#include "exercisewithtileswidget.h"
#include "ui_exercisewithtileswidget.h"
#include <QEventLoop>
#include <QTimer>

ExerciseWithTilesWidget::ExerciseWithTilesWidget(QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::ExerciseWithTilesWidget)
    , tiles(new NoteTilesWidget(this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(tiles);

    connect(ui->startBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::startClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, [this] (){
        emit backClicked();
    });
    connect(tiles, &NoteTilesWidget::noteSelected, this, &ExerciseWithTilesWidget::noteSelected);
    connect(this, &ExerciseWithTilesWidget::requestSetMode,
        this, &ExerciseWithTilesWidget::setMode);
}

ExerciseWithTilesWidget::~ExerciseWithTilesWidget()
{
    delete ui;
}

void ExerciseWithTilesWidget::showResult(const QVector<QString>& correct) {
    tiles->highlight(correct);
    QTimer::singleShot(2000, this, [this]() {
        emit requestSetMode(Mode::Input);
    });
}

void ExerciseWithTilesWidget::setMode(Mode m) {
    tiles->setMode(m);
}
