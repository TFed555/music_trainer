#include "chordinversionsession.h"

ChordInversionSession::ChordInversionSession(NotePlayer* player,
                                           QObject *parent)
    : ISession{parent}
{
    exerciseController = new ChordInversionController(player, this);
    noTilesView = new ExerciseNoTilesWidget(nullptr);
    view = noTilesView;

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &ChordInversionController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &ChordInversionController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &ChordInversionController::showResult,
            noTilesView, &ExerciseNoTilesWidget::showResult);

    connect(noTilesView, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &ChordInversionController::answerSelected);

    connect(exerciseController, &ChordInversionController::setAnswers,
            noTilesView, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &ChordInversionController::exercisePlayFinished,
            noTilesView, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(noTilesView, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &ChordInversionController::setDifficulty);

    exerciseController->giveAnswers();
}
