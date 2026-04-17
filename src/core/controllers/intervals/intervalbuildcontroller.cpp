#include "intervalbuildcontroller.h"
#include "../music/musicutils.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalBuildController::IntervalBuildController(NotePlayer* player,
                                                 QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    description = tr("Постройте интервал от \nподсвеченной ноты");
}

void IntervalBuildController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    IntervalGenerator gen(config);
    result = gen.generate();
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[secondNoteIdx]));
    emit setQuestion(result.interval);
    emit requestSetMode(Mode::Question);
    emit highlightQuestion({MusicUtils::midiToNote(result.midiNotes[firstNoteIdx])});
    log(result.desc);
    playTask();
}

void IntervalBuildController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes({result.midiNotes[firstNoteIdx]});
}

void IntervalBuildController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
    replayCount = config.replayCount;
}

void IntervalBuildController::noteSelected(const QString& noteName, const bool listenOnly) {
    qDebug() << "Note selected" << noteName;
    if (listenOnly) return;
    userAnswer.append(noteName);
    if (correctAnswer.size() > 0) {
        emit attemptDone({
            .exerciseId = "interval.build",
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
