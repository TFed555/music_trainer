#include "intervalbuildcontroller.h"
#include "../music/pitchutils.h"

IntervalBuildController::IntervalBuildController(NotePlayer* player,
                                                 QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playlistEmpty, [this]() {
        emit exercisePlayFinished();
    });
}

void IntervalBuildController::start() {
    playTone();
}

void IntervalBuildController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    // emit requestSetMode(Mode::Wait);
    notePlayer->playExercise(GeneratorType::Interval, 1);
}

void IntervalBuildController::stop() {
    notePlayer->stop();
}

void IntervalBuildController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    if (correctAnswer.size() > 0) {
        emit showResult(correctAnswer);
        emit requestSetMode(Mode::Result);
    }
}

void IntervalBuildController::onNotesPlayed(const GeneratedAudio& result){
    correctAnswer.clear();
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[1]));
    setQuestion(result.interval);
}
