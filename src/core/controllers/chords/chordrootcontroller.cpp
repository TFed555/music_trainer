#include "chordrootcontroller.h"
#include "../../music/pitchutils.h"
#include "../../generators/chords/chordgenerator.h"

ChordRootController::ChordRootController(NotePlayer* player,
                                         QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{

}

void ChordRootController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    emit requestSetMode(Mode::Wait);
    ChordGenerator gen(config);
    auto result = gen.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    correctAnswer.append(result.root);
    notePlayer->playChord(result.midiNotes);
}

void ChordRootController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
}

void ChordRootController::noteSelected(const QString& noteName) {
    qDebug() << "Note selected" << noteName;
    userAnswer.append(noteName);
    if (correctAnswer.size() > 0) {
        emit showResult(correctAnswer, userAnswer);
        emit requestSetMode(Mode::Result);
        correctAnswer.clear();
    }
}
