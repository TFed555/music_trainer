#include "intervalidentifycontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalIdentifyController::IntervalIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void IntervalIdentifyController::generateTask() {
    correctAnswer = 0;
    userAnswer = 0;
    IntervalGenerator gen(config);
    result = gen.generate();
    correctAnswer = result.interval;
    log(result.desc);
    playTask();
}

void IntervalIdentifyController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void IntervalIdentifyController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
    replayCount = config.replayCount;
}

void IntervalIdentifyController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit attemptDone({
        .exerciseId = "interval.identify",
        .correctAnswer = correctAnswer,
        .userAnswer = userAnswer,
        .correct = (userAnswer == correctAnswer),
        .timestamp = QDateTime::currentDateTime()
    });
    emit showResult(correctAnswer);
}
