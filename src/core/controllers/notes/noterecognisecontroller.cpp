#include "noterecognisecontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteRecogniseController::NoteRecogniseController(NotePlayer* player,
                                                 QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{

}

void NoteRecogniseController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    emit requestSetMode(Mode::Wait);
    NoteGenerator generator(config);
    auto result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[0]));
    notePlayer->playNotes(result.midiNotes);
}

void NoteRecogniseController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<NoteDifficultyConfig>[dif];
}

void NoteRecogniseController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    if (correctAnswer.size() > 0) {
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
    }
}
