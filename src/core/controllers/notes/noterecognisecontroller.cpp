#include "noterecognisecontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteRecogniseController::NoteRecogniseController(NotePlayer* player,
                                                 QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void NoteRecogniseController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    emit requestSetMode(Mode::Wait);
    NoteGenerator generator(config);
    result = generator.generate();
    log(result.desc);
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[0]));
    playTask();
}

void NoteRecogniseController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void NoteRecogniseController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = noteRecogniseDifficulty[dif];
    replayCount = config.replayCount;
}

void NoteRecogniseController::noteSelected(const QString& noteName, const bool listenOnly) {
    qDebug() << "Note selected" << noteName;
    if (listenOnly) return;
    userAnswer.append(noteName);
    if (correctAnswer.size() > 0) {
            emit attemptDone({
                .exerciseId = "note.recognise",
                .correctAnswer = vecToStr(correctAnswer),
                .userAnswer = vecToStr(userAnswer),
                .correct = (userAnswer == correctAnswer),
                .timestamp = QDateTime::currentDateTime()
            });
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
            correctAnswer.clear();
    }
}
