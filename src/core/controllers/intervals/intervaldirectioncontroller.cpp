#include "intervaldirectioncontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalDirectionController::IntervalDirectionController(NotePlayer* player,
                                                         QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void IntervalDirectionController::playTone() {
    IntervalGenerator gen(config);
    auto result = gen.generate();
    correctDirection = result.direction;
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
    QString correct = (correctDirection == IntervalDirection::Ascending)
                            ? "Ascending" : "Descending";
    emit showResult(correct);
}
