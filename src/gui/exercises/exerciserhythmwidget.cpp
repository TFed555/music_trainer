#include "exerciserhythmwidget.h"
#include "ui_exerciserhythmwidget.h"

ExerciseRhythmWidget::ExerciseRhythmWidget(QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::ExerciseRhythmWidget)
    , canvas(new RhythmCanvasWidget(this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(canvas);
    connect(ui->startBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::startClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, [this] (){
        emit backClicked();
    });
    for (auto* btn : this->findChildren<QPushButton*>()) {
        btn->setFocusPolicy(Qt::NoFocus);
    }
    ui->difficultyBox->setFocusPolicy(Qt::NoFocus);
}

ExerciseRhythmWidget::~ExerciseRhythmWidget()
{
    delete ui;
}

void ExerciseRhythmWidget::setRhythmNotes(const QVector<MusicUtils::Rhythm::RhythmType>& notes) {
    canvas->setNotes(notes);
}


void ExerciseRhythmWidget::exercisePlayFinished() {

}
