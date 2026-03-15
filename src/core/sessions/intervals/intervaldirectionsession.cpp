#include "intervaldirectionsession.h"

IntervalDirectionSession::IntervalDirectionSession(NotePlayer* player,
                                                 QObject* parent)
    : ISession(parent)
{
    exerciseController = new IntervalDirectionController(player, this);
    noTilesView = new ExerciseNoTilesWidget(nullptr);
    view = noTilesView;

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &IntervalDirectionController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &IntervalDirectionController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(noTilesView, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &IntervalDirectionController::answerSelected);

    connect(exerciseController, &IntervalDirectionController::exercisePlayFinished,
            noTilesView, &ExerciseNoTilesWidget::exercisePlayFinished);

    noTilesView->addDirectionSelector();

    connect(noTilesView, &ExerciseNoTilesWidget::directionSelected,
            exerciseController, &IntervalDirectionController::answerSelected);

    connect(exerciseController, &IntervalDirectionController::showResult,
            noTilesView, &ExerciseNoTilesWidget::showDirectionResult);

    connect(noTilesView, &ExerciseNoTilesWidget::directionSelected,
            exerciseController, &IntervalDirectionController::answerSelected);

    connect(noTilesView, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &IntervalDirectionController::setDifficulty);
}
