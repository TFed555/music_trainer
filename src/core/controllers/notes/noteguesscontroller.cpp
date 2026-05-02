#include "noteguesscontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteGuessController::NoteGuessController(NotePlayer* player,
                                         QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void NoteGuessController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    NoteGenerator generator(config);
    result = generator.generate();
    log(result.desc);
    correctAnswer = result.midiNotes.first() == result.midiNotes.last()
                        ? getAnswerVariants()[0] : getAnswerVariants()[1];
    playTask();
}

void NoteGuessController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void NoteGuessController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = noteGuessDifficulty[dif];
    replayCount = config.replayCount;
}

void NoteGuessController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit attemptDone({
        .exerciseId = "note.guess",
        .correctAnswer = correctAnswer,
        .userAnswer = userAnswer,
        .correct = (userAnswer == correctAnswer),
        .timestamp = QDateTime::currentDateTime()
    });
    emit showResult(correctAnswer);
}
