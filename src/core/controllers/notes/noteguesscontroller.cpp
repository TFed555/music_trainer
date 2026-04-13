#include "noteguesscontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteGuessController::NoteGuessController(NotePlayer* player,
                                         QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    answerVariants = {"одинаковые", "разные"};
    description = tr("Определите одинаковые или разные \nпервая и последняя ноты в мелодии");
}

void NoteGuessController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    NoteGenerator generator(config);
    result = generator.generate();
    log(result.desc);
    correctAnswer = result.midiNotes.first() == result.midiNotes.last()
                        ? answerVariants[0] : answerVariants[1];
    playTask();
}

void NoteGuessController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void NoteGuessController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = noteGuessDifficulty[dif];
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
