#include "chordinversioncontroller.h"
#include "../../generators/chords/chordgenerator.h"
using namespace MusicUtils::Chords;

ChordInversionController::ChordInversionController(NotePlayer* player,
                                                       QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
    answerVariants = MusicUtils::Chords::inversionNames.values();
}

void ChordInversionController::playTone() {
    correctAnswer = 0;
    userAnswer = 0;
    ChordGenerator gen(config);
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

void ChordInversionController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    config.allowedInversions = {InversionType::Root, InversionType::First, InversionType::Second};
}
