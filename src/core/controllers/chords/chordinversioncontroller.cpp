#include "chordinversioncontroller.h"
#include "../../generators/chords/chordgenerator.h"

ChordInversionController::ChordInversionController(NotePlayer* player,
                                                       QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void ChordInversionController::playTone() {
    correctAnswer = 0;
    userAnswer = 0;
    ChordGenerator gen({});
    auto result = gen.generate();
    correctAnswer = result.inversion;
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playChord(result.midiNotes);
}

void ChordInversionController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit showResult(correctAnswer);
}

void ChordInversionController::giveAnswers()
{
    emit setAnswers(answerVariants);
}
