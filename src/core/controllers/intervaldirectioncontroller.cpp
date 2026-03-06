#include "intervaldirectioncontroller.h"

IntervalDirectionController::IntervalDirectionController(NotePlayer* player,
                                                         QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playlistEmpty, this, [this]() {
        emit exercisePlayFinished();
    });
}

void IntervalDirectionController::playTone() {
    notePlayer->playExercise(GeneratorType::Interval, 2);
}


void IntervalDirectionController::onNotesPlayed(const GeneratedAudio& result) {
    correctDirection = result.direction;
}

void IntervalDirectionController::answerSelected(const QString& answer) {
    userAnswer = answer;
    QString correct = (correctDirection == IntervalDirection::Ascending)
                            ? "Ascending" : "Descending";
    emit showResult(correct);
}
