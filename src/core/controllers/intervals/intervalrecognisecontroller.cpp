#include "intervalrecognisecontroller.h"
#include "../../music/pitchutils.h"
#include "../../generators/intervals/IntervalGenerator.h"

IntervalRecogniseController::IntervalRecogniseController(NotePlayer* player,
                                                         QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playlistEmpty, this, [this]() {
        emit exercisePlayFinished();
    });
}

void IntervalRecogniseController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    emit requestSetMode(Mode::Wait);
    IntervalGenerator generator;
    auto result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[0]));
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[1]));

    notePlayer->playNotes(result.midiNotes);

}

void IntervalRecogniseController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    noteCounter++;
    if (noteCounter == 2) {
        if (correctAnswer.size() == 2) {
            emit showResult(correctAnswer, userAnswer);
            emit requestSetMode(Mode::Result);
        }
    }
}
