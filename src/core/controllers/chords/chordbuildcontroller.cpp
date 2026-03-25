#include "chordbuildcontroller.h"
#include "../music/pitchutils.h"
#include "../../generators/chords/chordgenerator.h"

ChordBuildController::ChordBuildController(NotePlayer* player,
                                           QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void ChordBuildController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    ChordGenerator gen(config);
    auto result = gen.generate();
    correctAnswer = {MusicUtils::midiToNote(result.midiNotes[secondNoteIdx]),
                    MusicUtils::midiToNote(result.midiNotes[thirdNoteIdx])};
    emit setQuestion(result.type);
    emit requestSetMode(Mode::Question);
    emit highlightQuestion({MusicUtils::midiToNote(result.midiNotes[firstNoteIdx])});
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes({result.midiNotes[firstNoteIdx]});
}

void ChordBuildController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    config.allowedInversions = {MusicUtils::Chords::InversionType::Root};
}

void ChordBuildController::noteSelected(const QString& noteName) {
    qDebug() << "Note selected" << noteName;
    userAnswer.append(noteName);
    noteCounter++;
    if (noteCounter == chordNoteCount) {
        if (correctAnswer.size() > 0) {
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
            correctAnswer.clear();
        }
    }
}
