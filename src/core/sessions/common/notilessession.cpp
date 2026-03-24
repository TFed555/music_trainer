#include "notilessession.h"

void NoTilesSession::setup(IExerciseController* ctrl, ExerciseNoTilesWidget* w) {
    view = w;
    connect(view, &ExerciseNoTilesWidget::startClicked, ctrl, &IExerciseController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, ctrl, &IExerciseController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(ctrl, &IExerciseController::exercisePlayFinished,
            w, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(w, &ExerciseNoTilesWidget::difficultyChanged,
            ctrl, &IExerciseController::setDifficulty);
}
