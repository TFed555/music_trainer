#include "intervalrecognisecontroller.h"
#include "../../music/musicutils.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalRecogniseController::IntervalRecogniseController(NotePlayer* player,
                                                         QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    description = tr("Укажите интервал на клавиатуре");
}

void IntervalRecogniseController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    emit requestSetMode(Mode::Wait);
    IntervalGenerator generator(config);
    result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[firstNoteIdx]));
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[secondNoteIdx]));
    playTask();
}

void IntervalRecogniseController::playTask() {
    notePlayer->playNotes(result.midiNotes);
}

void IntervalRecogniseController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<IntervalDifficultyConfig>[dif];
    replayCount = config.replayCount;
}

void IntervalRecogniseController::noteSelected(const QString& noteName, const bool listenOnly) {
    qDebug() << "Note selected" << noteName;
    if (listenOnly) return;
    userAnswer.append(noteName);
    noteCounter++;
    if (noteCounter == intervalNoteCount) {
        if (correctAnswer.size() == intervalNoteCount) {
            emit attemptDone({
                .exerciseId = "interval.recognise",
                .correctAnswer = vecToStr(correctAnswer),
                .userAnswer = vecToStr(userAnswer),
                .correct = (userAnswer == correctAnswer),
                .timestamp = QDateTime::currentDateTime()
            });
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
        }
    }
}
