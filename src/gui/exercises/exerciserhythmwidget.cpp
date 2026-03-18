#include "exerciserhythmwidget.h"
#include "ui_exerciserhythmwidget.h"

ExerciseRhythmWidget::ExerciseRhythmWidget(QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::ExerciseRhythmWidget)
{
    ui->setupUi(this);
    connect(ui->startBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::startClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, [this] (){
        emit backClicked();
    });
}

ExerciseRhythmWidget::~ExerciseRhythmWidget()
{
    delete ui;
}

void ExerciseRhythmWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {

    }
}

void ExerciseRhythmWidget::exercisePlayFinished() {

}
