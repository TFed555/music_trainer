#include "noteguesscontroller.h"
#include "../../generators/notes/notegenerator.h"

NoteGuessController::NoteGuessController(NotePlayer* player,
                                         QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
    answerVariants = {"одинаковые", "разные"};
}

void NoteGuessController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    NoteGenerator generator(config);
    auto result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
    correctAnswer = result.midiNotes.first() == result.midiNotes.last()
                        ? answerVariants[0] : answerVariants[1];
}

void NoteGuessController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = noteGuessDifficulty[dif];
}

void NoteGuessController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit showResult(correctAnswer);
}
