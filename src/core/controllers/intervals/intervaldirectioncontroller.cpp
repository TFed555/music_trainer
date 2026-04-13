#include "intervaldirectioncontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalDirectionController::IntervalDirectionController(NotePlayer* player,
                                                         QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    answerVariants = directionMap.values();
    description = tr("Укажите направление интервала");
}

void IntervalDirectionController::generateTask() {
    IntervalGenerator gen(config);
    result = gen.generate();
    correctAnswer = directionMap[result.direction];
    log(result.desc);
    playTask();
}

void IntervalDirectionController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void IntervalDirectionController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
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
