#include "noteguesssession.h"

NoteGuessSession::NoteGuessSession(NotePlayer* player,
                                    QObject* parent)
    : ISession(parent)
{
    exerciseController = new NoteGuessController(player, this);
    view = new ExerciseNoTilesWidget(nullptr);

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &NoteGuessController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &NoteGuessController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &NoteGuessController::showResult,
            view, &ExerciseNoTilesWidget::showResult);

    connect(view, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &NoteGuessController::answerSelected);

    connect(exerciseController, &NoteGuessController::setAnswers,
            view, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &NoteGuessController::exercisePlayFinished,
            view, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(view, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &NoteGuessController::setDifficulty);

    exerciseController->giveAnswers();
}
