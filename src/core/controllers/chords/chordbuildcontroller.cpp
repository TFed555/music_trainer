#include "chordbuildcontroller.h"
#include "../music/musicutils.h"
#include "../../generators/chords/chordgenerator.h"

ChordBuildController::ChordBuildController(NotePlayer* player,
                                           QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void ChordBuildController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    ChordGenerator gen(config);
    result = gen.generate();
    correctAnswer = {MusicUtils::midiToNote(result.midiNotes[secondNoteIdx]),
                     MusicUtils::midiToNote(result.midiNotes[thirdNoteIdx])};
    emit setQuestion(result.type);
    emit requestSetMode(Mode::Question);
    emit highlightQuestion({MusicUtils::midiToNote(result.midiNotes[firstNoteIdx])});
    log(result.desc);
    playTask();
}

void ChordBuildController::playTask() {
    LOG_DEBUG(QString("%1 %2").arg(playbackLog.last().timestamp.toString(), playbackLog.last().desc));
    notePlayer->playNotes({result.midiNotes[firstNoteIdx]});
}

void ChordBuildController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    config.allowedInversions = {MusicUtils::Chords::InversionType::Root};
    replayCount = config.replayCount;
    emit setOctaveCount(config.octaveCount);
}

void ChordBuildController::noteSelected(const QString& noteName, const bool listenOnly) {
    LOG_DEBUG(QString("Note selected %1").arg(noteName));
    if (listenOnly) return;
    userAnswer.append(noteName);
    noteCounter++;
    if (noteCounter == chordNoteCount) {
        if (correctAnswer.size() > 0) {
            emit attemptDone({
                .exerciseId = "chord.build",
                .correctAnswer = vecToStr(correctAnswer),
                .userAnswer = vecToStr(userAnswer),
                .correct = (userAnswer == correctAnswer),
                .timestamp = QDateTime::currentDateTime()
            });
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
            emit replayAvailable(replayCount);
            correctAnswer.clear();
        }
    }
}
