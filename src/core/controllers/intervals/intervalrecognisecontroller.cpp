#include "intervalrecognisecontroller.h"
#include "../../music/pitchutils.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalRecogniseController::IntervalRecogniseController(NotePlayer* player,
                                                         QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void IntervalRecogniseController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    emit requestSetMode(Mode::Wait);
    IntervalGenerator generator(config);
    auto result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[firstNoteIdx]));
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[secondNoteIdx]));

    notePlayer->playNotes(result.midiNotes);

}

void IntervalRecogniseController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
}

void IntervalRecogniseController::noteSelected(const QString& noteName) {
    qDebug() << "Note selected" << noteName;
    userAnswer.append(noteName);
    noteCounter++;
    if (noteCounter == intervalNoteCount) {
        if (correctAnswer.size() == intervalNoteCount) {
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
        }
    }
}
