#include "intervalexercisewidget.h"
#include "ui_intervalexercisewidget.h"
#include "../../audio/generators/generatorfactory.h"
#include "../music/pitchutils.h"

IntervalExerciseWidget::IntervalExerciseWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IntervalExerciseWidget)
{
    ui->setupUi(this);
    auto* tiles = new NoteTilesWidget(this);
    ui->horizontalLayout->addWidget(tiles);

    processor = new AudioProcessor(this);
    connect(processor, &AudioProcessor::playbackFinished,
            this, []() { qDebug() << "Playback finished"; });
    connect(processor, &AudioProcessor::err,
            this, [](const QString& msg) { qDebug() << "Error:" << msg; });
    connect(ui->startBtn, &QPushButton::clicked, this, &IntervalExerciseWidget::playTone);
    connect(ui->stopBtn, &QPushButton::clicked, processor, &AudioProcessor::stopPlayback);
    connect(processor, &AudioProcessor::notePlayed,
            this, [this](const GeneratedAudio& result) {
                qDebug() << "Played:" << result.desc;
                correctAnswer.append(MusicTheory::midiToNote(result.midiNotes[0]));
                correctAnswer.append(MusicTheory::midiToNote(result.midiNotes[1]));
            });
    connect(tiles, &NoteTilesWidget::noteSelected,
            this, [this](int idx, const QString& name){
                qDebug() << "Note selected" << name;
                userAnswer.append(name);
                noteCounter++;
                if (noteCounter == 2) {
                    emit inputFinished();
                }
    });
    connect(this, &IntervalExerciseWidget::inputFinished, this, [this, tiles]() {
        if (correctAnswer.size() == 2)
            emit requestSetMode(NoteTilesWidget::Mode::Result);
            tiles->highlight(correctAnswer);
    });
    connect(this, &IntervalExerciseWidget::requestSetMode,
            tiles, &NoteTilesWidget::setMode,
            Qt::QueuedConnection);
}

IntervalExerciseWidget::~IntervalExerciseWidget()
{
    delete ui;
}

void IntervalExerciseWidget::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    emit requestSetMode(NoteTilesWidget::Mode::Input);
    GeneratorParams params;

    auto gen = GeneratorFactory::instance()
                   .create(GeneratorType::Interval, params);

    processor->setGenerator(std::move(gen));
    processor->play(2.0f);
}
