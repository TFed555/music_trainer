#include "intervalbuildcontroller.h"
#include "../music/pitchutils.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalBuildController::IntervalBuildController(NotePlayer* player,
                                                 QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{

}

void IntervalBuildController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    IntervalGenerator gen(config);
    auto result = gen.generate();
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[1]));
    emit setQuestion(result.interval);
    emit requestSetMode(Mode::Question);
    emit highlightQuestion({MusicUtils::midiToNote(result.midiNotes[0])});
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes({result.midiNotes[0]});
}

void IntervalBuildController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
}

void IntervalBuildController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    if (correctAnswer.size() > 0) {
        emit showResult(correctAnswer, userAnswer);
        emit requestSetMode(Mode::Result);
        correctAnswer.clear();
    }
}
