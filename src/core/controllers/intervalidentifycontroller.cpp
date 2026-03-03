#include "intervalidentifycontroller.h"

IntervalIdentifyController::IntervalIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playlistEmpty, [this]() {
        emit exercisePlayFinished();
    });
}

void IntervalIdentifyController::start() {
    playTone();
}

void IntervalIdentifyController::playTone() {
    correctAnswer = 0;
    userAnswer = 0;
    notePlayer->playExercise(GeneratorType::Interval, 2);
}

void IntervalIdentifyController::stop() {
    notePlayer->stop();
}

void IntervalIdentifyController::onNotesPlayed(const GeneratedAudio& result) {
    correctAnswer = 0;
    correctAnswer = result.interval;
}

void IntervalIdentifyController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit showResult(correctAnswer);
}

void IntervalIdentifyController::giveAnswers()
{
    emit setAnswers(answerVariants);
}
