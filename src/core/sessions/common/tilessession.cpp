#include "tilessession.h"

void TilesSession::setup(ITilesExerciseController* ctrl, TilesController* tilesctrl, ExerciseWithTilesWidget* w) {
    view = w;
    connect(view, &ExerciseWithTilesWidget::startClicked, ctrl, &ITilesExerciseController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, ctrl, &ITilesExerciseController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect (ctrl, &ITilesExerciseController::showResult,
            w, &ExerciseWithTilesWidget::showResult);

    connect(ctrl, &ITilesExerciseController::requestSetMode,
            w, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(w, &ExerciseWithTilesWidget::noteSelected,
            tilesctrl, &TilesController::playTile);

    connect(w, &ExerciseWithTilesWidget::noteSelected,
            ctrl, &ITilesExerciseController::noteSelected);

    connect(ctrl, &ITilesExerciseController::exercisePlayFinished,
            w, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(w, &ExerciseWithTilesWidget::difficultyChanged,
            ctrl, &ITilesExerciseController::setDifficulty);

    connect(ctrl, &ITilesExerciseController::setQuestion,
                     w, &ExerciseWithTilesWidget::setQuestion);

    connect(ctrl, &ITilesExerciseController::highlightQuestion,
                     w, &ExerciseWithTilesWidget::highlightQuestion);
}
