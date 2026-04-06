#include "notebuildcontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteBuildController::NoteBuildController(NotePlayer* player,
                                           QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void NoteBuildController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    NoteGenerator gen(config);
    auto result = gen.generate();
    correctAnswer = {MusicUtils::midiToNote(result.midiNotes[0])};
    emit setQuestion(result.desc);
    emit requestSetMode(Mode::Question);
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes({result.midiNotes[0]});
}

void NoteBuildController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = noteBuildDifficulty[dif];
    emit setOctaveCount(config.octaveCount);
}

void NoteBuildController::noteSelected(const QString& noteName) {
    qDebug() << "Note selected" << noteName;
    userAnswer.append(noteName);
    if (correctAnswer.size() > 0) {
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
            correctAnswer.clear();
    }
}
