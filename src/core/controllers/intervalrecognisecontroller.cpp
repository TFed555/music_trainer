#include "intervalrecognisecontroller.h"
#include "../../music/pitchutils.h"

IntervalRecogniseController::IntervalRecogniseController(NotePlayer* player)
    : notePlayer(player)
{
    connect(notePlayer, &NotePlayer::playbackFinished,
            this, []() { qDebug() << "Playback finished"; });
    connect(notePlayer, &NotePlayer::error,
            this, [](const QString& msg) { qDebug() << "Error:" << msg; });
    connect(notePlayer, &NotePlayer::notesPlayed,
            this, [this](const GeneratedAudio& result) {
                qDebug() << "Played:" << result.desc;
                correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[0]));
                correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[1]));
            });
}


void IntervalRecogniseController::start() {
    playTone();
}

void IntervalRecogniseController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    noteCounter = 0;
    emit requestSetMode(Mode::Input);
    notePlayer->playExercise(GeneratorType::Interval);
}

void IntervalRecogniseController::stop() {
    notePlayer->stop();
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
