#include "chordidentifycontroller.h"
#include "../../generators/chords/chordgenerator.h"

ChordIdentifyController::ChordIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void ChordIdentifyController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    ChordGenerator gen({.allowedTypes={MusicUtils::Chords::ChordType::Major, MusicUtils::Chords::ChordType::Minor},
                        .allowedInversions={MusicUtils::Chords::InversionType::Root}});
    auto result = gen.generate();
    correctAnswer = result.type;
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playChord(result.midiNotes);
}

void ChordIdentifyController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit showResult(correctAnswer);
}

void ChordIdentifyController::giveAnswers()
{
    emit setAnswers(answerVariants);
}
