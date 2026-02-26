#include "intervalexercisewidget.h"
#include "ui_intervalexercisewidget.h"
#include "../../audio/generators/generatorfactory.h"
#include "../music/pitchutils.h"
#include <QEventLoop>
#include <QTimer>

IntervalExerciseWidget::IntervalExerciseWidget(NotePlayer* player, QWidget *parent)
    : notePlayer(player)
    , QWidget(parent)
    , ui(new Ui::IntervalExerciseWidget)
{
    ui->setupUi(this);
    auto* tiles = new NoteTilesWidget(notePlayer, this);
    ui->horizontalLayout->addWidget(tiles);

    connect(notePlayer, &NotePlayer::playbackFinished,
            this, []() { qDebug() << "Playback finished"; });
    connect(notePlayer, &NotePlayer::error,
            this, [](const QString& msg) { qDebug() << "Error:" << msg; });
    connect(ui->startBtn, &QPushButton::clicked, this, &IntervalExerciseWidget::playTone);
    connect(ui->stopBtn, &QPushButton::clicked, notePlayer, &NotePlayer::stop);
    connect(notePlayer, &NotePlayer::notesPlayed,
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
            QEventLoop loop;
            QTimer::singleShot(2000, &loop, &QEventLoop::quit);
            loop.exec();
            emit requestSetMode(NoteTilesWidget::Mode::Input);
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
    notePlayer->playExercise(GeneratorType::Interval);
}
