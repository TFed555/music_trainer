#include "intervalidentifycontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalIdentifyController::IntervalIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playlistEmpty, this, [this]() {
        emit exercisePlayFinished();
    });
}

void IntervalIdentifyController::playTone() {
    correctAnswer = 0;
    userAnswer = 0;
    IntervalGenerator gen;
    auto result = gen.generate();
    correctAnswer = result.interval;
    log(result.desc);
    notePlayer->playNotes(result.midiNotes);
    // notePlayer->playExercise(GeneratorType::Interval, 2);
}

void IntervalIdentifyController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit showResult(correctAnswer);
}

void IntervalIdentifyController::giveAnswers()
{
    emit setAnswers(answerVariants);
}
