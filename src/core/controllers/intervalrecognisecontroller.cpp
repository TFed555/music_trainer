#include "intervalrecognisecontroller.h"
#include "../../music/pitchutils.h"

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
    notePlayer->playExercise(GeneratorType::Interval, 2);
}

void IntervalRecogniseController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    noteCounter++;
    if (noteCounter == 2) {
        if (correctAnswer.size() == 2) {
            emit showResult(correctAnswer);
            emit requestSetMode(Mode::Result);
        }
    }
}

void IntervalRecogniseController::onNotesPlayed(const GeneratedAudio& result){
    correctAnswer.clear();
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[0]));
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[1]));
}

