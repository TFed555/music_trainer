#include "noteguesssession.h"

NoteGuessSession::NoteGuessSession(NotePlayer* player,
                                    QObject* parent)
    : ISession(parent)
{
    exerciseController = new NoteGuessController(player, this);
    noTilesView = new ExerciseNoTilesWidget(nullptr);
    view = noTilesView;

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &NoteGuessController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &NoteGuessController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &NoteGuessController::showResult,
            noTilesView, &ExerciseNoTilesWidget::showResult);

    connect(noTilesView, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &NoteGuessController::answerSelected);

    connect(exerciseController, &NoteGuessController::setAnswers,
            noTilesView, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &NoteGuessController::exercisePlayFinished,
            noTilesView, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(noTilesView, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &NoteGuessController::setDifficulty);

    exerciseController->giveAnswers();
}
