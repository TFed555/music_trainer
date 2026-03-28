#include "intervalidentifycontroller.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalIdentifyController::IntervalIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    answerVariants = MusicUtils::Intervals::intervals;
}

void IntervalIdentifyController::playTone() {
    correctAnswer = 0;
    userAnswer = 0;
    IntervalGenerator gen(config);
    auto result = gen.generate();
    correctAnswer = result.interval;
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void IntervalIdentifyController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
}

void IntervalIdentifyController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit showResult(correctAnswer);
}
