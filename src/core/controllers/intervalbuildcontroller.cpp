#include "intervalbuildcontroller.h"
#include "../music/pitchutils.h"

IntervalBuildController::IntervalBuildController(NotePlayer* player,
                                                 QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playlistEmpty, this, [this]() {
        emit exercisePlayFinished();
    });
}

void IntervalBuildController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    // emit requestSetMode(Mode::Wait);
    notePlayer->playExercise(GeneratorType::Interval, 1);
}

void IntervalBuildController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    if (correctAnswer.size() > 0) {
        emit showResult(correctAnswer, userAnswer);
        emit requestSetMode(Mode::Result);
        correctAnswer.clear();
    }
}

void IntervalBuildController::onNotesPlayed(const GeneratedAudio& result){
    correctAnswer.clear();
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[1]));
    setQuestion(result.interval);
    emit requestSetMode(Mode::Question);
    emit highlightQuestion({MusicUtils::midiToNote(result.midiNotes[0])});
}
