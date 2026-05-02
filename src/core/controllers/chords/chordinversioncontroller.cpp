#include "chordinversioncontroller.h"
#include "../../generators/chords/chordgenerator.h"
using namespace MusicUtils::Chords;

ChordInversionController::ChordInversionController(NotePlayer* player,
                                                       QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
    setDifficulty(0);
}

void ChordInversionController::generateTask() {
    correctAnswer = 0;
    userAnswer = 0;
    ChordGenerator gen(config);
    result = gen.generate();
    correctAnswer = result.inversion;
    log(result.desc);
    playTask();
}

void ChordInversionController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playChord(result.midiNotes);
}

void ChordInversionController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit attemptDone({
        .exerciseId = "chord.inversion",
        .correctAnswer = correctAnswer,
        .userAnswer = userAnswer,
        .correct = (userAnswer == correctAnswer),
        .timestamp = QDateTime::currentDateTime()
    });
    emit showResult(correctAnswer);
}

void ChordInversionController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    config.allowedInversions = {InversionType::Root, InversionType::First, InversionType::Second};
    replayCount = config.replayCount;
}
