#include "intervaldirectioncontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalDirectionController::IntervalDirectionController(NotePlayer* player,
                                                         QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void IntervalDirectionController::playTone() {
    // notePlayer->playExercise(GeneratorType::Interval, 2);
    IntervalGenerator gen;
    auto result = gen.generate();
    correctDirection = result.direction;
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void IntervalDirectionController::answerSelected(const QString& answer) {
    userAnswer = answer;
    QString correct = (correctDirection == IntervalDirection::Ascending)
                            ? "Ascending" : "Descending";
    emit showResult(correct);
}
