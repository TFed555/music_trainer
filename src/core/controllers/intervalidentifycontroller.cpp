#include "intervalidentifycontroller.h"

IntervalIdentifyController::IntervalIdentifyController(NotePlayer* player)
    : IExerciseController(player)
{

}

void IntervalIdentifyController::start() {
    playTone();
}

void IntervalIdentifyController::playTone() {
    correctAnswer = 0;
    userAnswer = 0;
    notePlayer->playExercise(GeneratorType::Interval);
}

void IntervalIdentifyController::stop() {
    notePlayer->stop();
}

void IntervalIdentifyController::onNotesPlayed(const GeneratedAudio& result) {
    correctAnswer.clear();
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
