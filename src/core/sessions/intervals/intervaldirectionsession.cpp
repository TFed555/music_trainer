#include "intervaldirectionsession.h"

IntervalDirectionSession::IntervalDirectionSession(NotePlayer* player,
                                                 QObject* parent)
    : ISession(parent)
{
    exerciseController = new IntervalDirectionController(player, this);
    view = new ExerciseNoTilesWidget(nullptr);

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &IntervalDirectionController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &IntervalDirectionController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(view, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &IntervalDirectionController::answerSelected);

    connect(exerciseController, &IntervalDirectionController::exercisePlayFinished,
            view, &ExerciseNoTilesWidget::exercisePlayFinished);

    view->addDirectionSelector();

    connect(view, &ExerciseNoTilesWidget::directionSelected,
            exerciseController, &IntervalDirectionController::answerSelected);

    connect(exerciseController, &IntervalDirectionController::showResult,
            view, &ExerciseNoTilesWidget::showDirectionResult);

    connect(view, &ExerciseNoTilesWidget::directionSelected,
            exerciseController, &IntervalDirectionController::answerSelected);

    connect(view, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &IntervalDirectionController::setDifficulty);
}
