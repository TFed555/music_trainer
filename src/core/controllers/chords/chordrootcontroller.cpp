#include "chordrootcontroller.h"
#include "../../music/musicutils.h"
#include "../../generators/chords/chordgenerator.h"

ChordRootController::ChordRootController(NotePlayer* player,
                                         QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void ChordRootController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    emit requestSetMode(Mode::Wait);
    ChordGenerator gen(config);
    result = gen.generate();
    log(result.desc);
    LOG_DEBUG(QString("%1 %2").arg(playbackLog.last().timestamp.toString(), playbackLog.last().desc));
    playTask();
}

void ChordRootController::playTask() {
    correctAnswer.append(result.root);
    notePlayer->playChord(result.midiNotes);
}

void ChordRootController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    replayCount = config.replayCount;
}

void ChordRootController::noteSelected(const QString& noteName, const bool listenOnly){
    LOG_DEBUG(QString("Note selected %1").arg(noteName));
    if (listenOnly) return;
    userAnswer.append(noteName);
    if (correctAnswer.size() > 0) {
        emit attemptDone({
            .exerciseId = "chord.root",
            .correctAnswer = vecToStr(correctAnswer),
            .userAnswer = vecToStr(userAnswer),
            .correct = (userAnswer == correctAnswer),
            .timestamp = QDateTime::currentDateTime()
        });
        emit showResult(correctAnswer, userAnswer);
        emit requestSetMode(Mode::Result);
        correctAnswer.clear();
    }
}
