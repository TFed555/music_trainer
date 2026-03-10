#include "chordinversionsession.h"

ChordInversionSession::ChordInversionSession(NotePlayer* player,
                                           QObject *parent)
    : ISession{parent}
{
    exerciseController = new ChordInversionController(player, this);
    view = new ExerciseNoTilesWidget(nullptr);

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &ChordInversionController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &ChordInversionController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &ChordInversionController::showResult,
            view, &ExerciseNoTilesWidget::showResult);

    connect(view, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &ChordInversionController::answerSelected);

    connect(exerciseController, &ChordInversionController::setAnswers,
            view, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &ChordInversionController::exercisePlayFinished,
            view, &ExerciseNoTilesWidget::exercisePlayFinished);

    exerciseController->giveAnswers();
}
