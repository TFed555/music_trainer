#include "chordidentifycontroller.h"
#include "../../generators/chords/chordgenerator.h"

ChordIdentifyController::ChordIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playlistEmpty, this, [this]() {
        emit exercisePlayFinished();
    });
}

void ChordIdentifyController::playTone() {
    correctAnswer = 0;
    userAnswer = 0;
    ChordGenerator gen;
    auto result = gen.generate();
    correctAnswer = result.tone;
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void ChordIdentifyController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit showResult(correctAnswer);
}

void ChordIdentifyController::giveAnswers()
{
    emit setAnswers(answerVariants);
}
