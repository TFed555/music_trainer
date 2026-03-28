#include "notilessession.h"

void NoTilesSession::setup(IChoiceExerciseController* ctrl, ExerciseNoTilesWidget* w) {
    view = w;
    connect(view, &ExerciseNoTilesWidget::startClicked, ctrl, &IChoiceExerciseController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, ctrl, &IChoiceExerciseController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(ctrl, &IChoiceExerciseController::exercisePlayFinished,
            w, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(w, &ExerciseNoTilesWidget::difficultyChanged,
            ctrl, &IChoiceExerciseController::setDifficulty);

    connect(ctrl, &IChoiceExerciseController::showResult,
            w,    &ExerciseNoTilesWidget::showResult);

    connect(w, &ExerciseNoTilesWidget::answerSelected,
            ctrl, &IChoiceExerciseController::answerSelected);

    connect(ctrl, &IChoiceExerciseController::setAnswers,
            w,    &ExerciseNoTilesWidget::addAnswers);

    ctrl->giveAnswers();
}
