#include "intervalexercisewidget.h"
#include "ui_intervalexercisewidget.h"
#include "../../audio/generators/IntervalGenerator.h"

IntervalExerciseWidget::IntervalExerciseWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IntervalExerciseWidget)
{
    ui->setupUi(this);
    processor = new AudioProcessor(this);
    connect(processor, &AudioProcessor::playbackFinished,
            this, []() { qDebug() << "Playback finished"; });
    connect(processor, &AudioProcessor::err,
            this, [](const QString& msg) { qDebug() << "Error:" << msg; });
    connect(ui->playBtn, &QPushButton::clicked, this, &IntervalExerciseWidget::playTone);
    connect(ui->stopBtn, &QPushButton::clicked, processor, &AudioProcessor::stopPlayback);
    connect(processor, &AudioProcessor::notePlayed,
            this, [](const QString& note) {
                qDebug() << "Played:" << note;
            });
}

IntervalExerciseWidget::~IntervalExerciseWidget()
{
    delete ui;
}

void IntervalExerciseWidget::playTone() {
    processor->setGenerator(std::make_unique<IntervalGenerator>());
    processor->play(2.0f);
}
