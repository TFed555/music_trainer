#include "intervalrecognisecontroller.h"

IntervalRecogniseController::IntervalRecogniseController(NotePlayer* player)
    : IExerciseController(player)
{
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
