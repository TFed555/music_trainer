#include "notebuildcontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteBuildController::NoteBuildController(NotePlayer* player,
                                           QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void NoteBuildController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    NoteGenerator gen(config);
    result = gen.generate();
    correctAnswer = {MusicUtils::midiToNote(result.midiNotes[0])};
    emit setQuestion(result.desc);
    emit requestSetMode(Mode::Question);
    log(result.desc);
    playTask();
}

void NoteBuildController::playTask() {
    LOG_DEBUG(QString("%1 %2").arg(playbackLog.last().timestamp.toString(), playbackLog.last().desc));
    notePlayer->playNotes({result.midiNotes[0]});
}

void NoteBuildController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = noteBuildDifficulty[dif];
    replayCount = config.replayCount;
    emit setOctaveCount(config.octaveCount);
}

void NoteBuildController::noteSelected(const QString& noteName, const bool listenOnly) {
    LOG_DEBUG(QString("Note selected %1").arg(noteName));    if (listenOnly) return;
    userAnswer.append(noteName);
    if (correctAnswer.size() > 0) {
            emit attemptDone({
                .exerciseId = "note.build",
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
