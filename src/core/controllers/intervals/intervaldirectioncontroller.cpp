#include "intervaldirectioncontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalDirectionController::IntervalDirectionController(NotePlayer* player,
                                                         QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    answerVariants = directionMap.values();
}

void IntervalDirectionController::playTone() {
    IntervalGenerator gen(config);
    auto result = gen.generate();
    correctAnswer = directionMap[result.direction];
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void IntervalDirectionController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
}

void IntervalDirectionController::answerSelected(const QString& answer) {
    userAnswer = answer;
    emit showResult(correctAnswer);
}
