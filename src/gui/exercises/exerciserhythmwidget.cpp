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
    connect(ui->startBtn, &QPushButton::clicked, this, [this] {
        emit startClicked();
        setMode(Mode::Wait);
    });
    // connect(ui->startBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::startClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, [this] (){
        emit backClicked();
    });
    connect(ui->replayBtn, &QPushButton::clicked, this, &ExerciseRhythmWidget::replayClicked);
    ui->replayBtn->setEnabled(false);
    connect(canvas, &RhythmCanvasWidget::inputFinished, this, &ExerciseRhythmWidget::inputFinished);
    for (auto* btn : this->findChildren<QPushButton*>()) {
        btn->setFocusPolicy(Qt::NoFocus);
    }
    QVector<QString> durations = durationNames();
    const QMap<QString, int> durationMap = {
        {durations[0], 1},
        {durations[1], 2},
        {durations[2], 4},
        {durations[3], 8},
        {durations[4], 16},
    };

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
            states[durationMap[box->text()]] = status;
            emit configChanged(states);
        });
    }
    ui->quarter->setChecked(true);
    ui->modeLabel->setText("");
}

ExerciseRhythmWidget::~ExerciseRhythmWidget()
{
    delete ui;
}

void ExerciseRhythmWidget::setRhythmNotes(const QVector<MusicUtils::Rhythm::RhythmType>& notes, int bpm) {
    canvas->setNotes(notes, bpm);
}

void ExerciseRhythmWidget::exercisePlayFinished() {
    setMode(Mode::Input);
    canvas->exerciseStarted();
}

void ExerciseRhythmWidget::getResult(const int correct, const int wrong) {
    QMessageBox::information(this, tr("Результат"), QString(tr("Количество попаданий: %1\n Количество ошибок: %2"))
                                                    .arg(correct).arg(wrong));

}

void ExerciseRhythmWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        canvas->handleTap();
    }
    IExerciseWidget::keyPressEvent(event);
}

void ExerciseRhythmWidget::setDescription(const QString& text) {
    ui->descriptionLabel->setText(text);
}

void ExerciseRhythmWidget::setMode(Mode m) {
    switch (m) {
    case Mode::Wait:
        ui->modeLabel->setText(tr("Слушайте"));
        break;
    case Mode::Input:
        ui->modeLabel->setText(tr("Введите ответ"));
        break;
    case Mode::Result:
        ui->modeLabel->setText("");
        break;
    case Mode::Question:
        ui->modeLabel->setText("");
        break;
    case Mode::Try:
        ui->modeLabel->setText("");
        break;
    }
}

void ExerciseRhythmWidget::retranslate() {
    ui->startBtn->setText(tr("Старт"));
    ui->stopBtn->setText(tr("Стоп"));
    ui->replayBtn->setText(tr("Повторить"));
    ui->backBtn->setText(tr("Назад"));
    QVector<QString> durations = durationNames();
    auto boxes = ui->layoutWidget2->findChildren<QCheckBox*>();
    for (int i = 0; i < boxes.size() && i < durations.size(); i++)
        boxes[i]->setText(durations[i]);
    emit langChange();
}
