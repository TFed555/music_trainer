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

    const QMap<QCheckBox*, int> durationMap = {
        {ui->checkBox_1, 1},
        {ui->checkBox_2, 2},
        {ui->checkBox_3, 4},
        {ui->checkBox_4, 8},
        {ui->checkBox_5, 16},
    };

    for (auto [box, dur] : durationMap.asKeyValueRange()) {
        states[dur] = box->isChecked() ? 1 : 0;
    }

    connect(ui->spinBox, &QSpinBox::editingFinished, this, [this]() {
        ui->spinBox->clearFocus();
    });
    ui->spinBox->setRange(30,244);
    ui->spinBox->setValue(80);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &ExerciseRhythmWidget::bpmChanged);

    for (auto* box : ui->layoutWidget2->findChildren<QCheckBox*>()) {
        box->setFocusPolicy(Qt::NoFocus);
        connect(box, &QCheckBox::checkStateChanged, this, [this, box, durationMap](Qt::CheckState state) {
            int status = state == Qt::CheckState::Unchecked ? 0 : 1;
            states[durationMap[box]] = status;
            emit configChanged(states);
        });
    }
    ui->checkBox_3->setChecked(true);
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

void ExerciseRhythmWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        canvas->handleTap();
    }
    IExerciseWidget::keyPressEvent(event);
}


