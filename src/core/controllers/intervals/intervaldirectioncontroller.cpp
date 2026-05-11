#include "intervaldirectioncontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalDirectionController::IntervalDirectionController(NotePlayer* player,
                                                         QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void IntervalDirectionController::generateTask() {
    IntervalGenerator gen(config);
    result = gen.generate();
    correctAnswer = intervalDirectionName(result.direction);
    log(result.desc);
    playTask();
}

void IntervalDirectionController::playTask() {
    LOG_DEBUG(QString("%1 %2").arg(playbackLog.last().timestamp.toString(), playbackLog.last().desc));
    notePlayer->playNotes(result.midiNotes);
}

void IntervalDirectionController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
    replayCount = config.replayCount;
}

void IntervalDirectionController::answerSelected(const QString& answer) {
    userAnswer = answer;
    emit attemptDone({
        .exerciseId = "interval.direction",
        .correctAnswer = correctAnswer,
        .userAnswer = userAnswer,
        .correct = (userAnswer == correctAnswer),
        .timestamp = QDateTime::currentDateTime()
    });
    emit showResult(correctAnswer);
}
