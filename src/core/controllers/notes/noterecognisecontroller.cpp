#include "noterecognisecontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteRecogniseController::NoteRecogniseController(NotePlayer* player,
                                                 QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    description = tr("Укажите услышанную ноту \nна клавиатуре");
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
}

void NoteRecogniseController::noteSelected(const QString& noteName) {
    qDebug() << "Note selected" << noteName;
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
