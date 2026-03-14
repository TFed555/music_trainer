#include "chordbuildcontroller.h"
#include "../music/pitchutils.h"
#include "../../generators/chords/chordgenerator.h"

ChordBuildController::ChordBuildController(NotePlayer* player,
                                           QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void ChordBuildController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    ChordGenerator gen(config);
    auto result = gen.generate();
    correctAnswer = {MusicUtils::midiToNote(result.midiNotes[1]),
                    MusicUtils::midiToNote(result.midiNotes[2])};
    emit setQuestion(result.type);
    emit requestSetMode(Mode::Question);
    emit highlightQuestion({MusicUtils::midiToNote(result.midiNotes[0])});
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes({result.midiNotes[0]});
}

void ChordBuildController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    config.allowedInversions = {MusicUtils::Chords::InversionType::Root};
}

void ChordBuildController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    noteCounter++;
    if (noteCounter == 2) {
        if (correctAnswer.size() > 0) {
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
            correctAnswer.clear();
        }
    }
}
