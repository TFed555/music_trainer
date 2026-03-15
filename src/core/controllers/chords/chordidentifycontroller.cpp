#include "chordidentifycontroller.h"
#include "../../generators/chords/chordgenerator.h"

ChordIdentifyController::ChordIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
    answerVariants = MusicUtils::Chords::chordTypeNames.values();
}

void ChordIdentifyController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    ChordGenerator gen(config);
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

void ChordIdentifyController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    config.allowedInversions = {MusicUtils::Chords::InversionType::Root};
}

