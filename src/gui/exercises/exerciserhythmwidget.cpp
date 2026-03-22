#include "exerciserhythmwidget.h"
#include "ui_exerciserhythmwidget.h"
#include <QMessageBox>

ExerciseRhythmWidget::ExerciseRhythmWidget(QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::ExerciseRhythmWidget)
    , canvas(new RhythmCanvasWidget(this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(canvas);
    ui->horizontalLayout->setSpacing(10);
    ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    connect(ui->startBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::startClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, [this] (){
        emit backClicked();
    });
    connect(canvas, &RhythmCanvasWidget::inputFinished, this, &ExerciseRhythmWidget::inputFinished);
    for (auto* btn : this->findChildren<QPushButton*>()) {
        btn->setFocusPolicy(Qt::NoFocus);
    }
    ui->difficultyBox->setFocusPolicy(Qt::NoFocus);
}

ExerciseRhythmWidget::~ExerciseRhythmWidget()
{
    delete ui;
}

void ExerciseRhythmWidget::setRhythmNotes(const QVector<MusicUtils::Rhythm::RhythmType>& notes, int bpm) {
    canvas->setNotes(notes, bpm);
}


void ExerciseRhythmWidget::exercisePlayFinished() {
    canvas->exerciseStarted();
}

void ExerciseRhythmWidget::getResult(const int correct, const int wrong) {
    QMessageBox::information(this, "Результат", QString("Количество попаданий: %1\n Количество ошибок: %2")
                                                    .arg(correct).arg(wrong));

}
