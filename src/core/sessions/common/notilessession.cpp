#include "notilessession.h"

void NoTilesSession::setup(IChoiceExerciseController* ctrl, ExerciseNoTilesWidget* w, StatisticsRepository* statsRepo) {
    view = w;
    connect(view, &ExerciseNoTilesWidget::startClicked, ctrl, &IChoiceExerciseController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, ctrl, &IChoiceExerciseController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(w, &ExerciseNoTilesWidget::replayClicked, ctrl, &IChoiceExerciseController::replay);

    connect(ctrl, &IChoiceExerciseController::exercisePlayFinished,
            w, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(w, &ExerciseNoTilesWidget::difficultyChanged,
            ctrl, &IChoiceExerciseController::setDifficulty);

    connect(ctrl, &IChoiceExerciseController::showResult,
            w,    &ExerciseNoTilesWidget::showResult);

    connect(w, &ExerciseNoTilesWidget::answerSelected,
            ctrl, &IChoiceExerciseController::answerSelected);

    connect(ctrl, &IChoiceExerciseController::setAnswers,
            w,  &ExerciseNoTilesWidget::addAnswers);

    connect(ctrl, &IChoiceExerciseController::attemptDone,
            statsRepo, &StatisticsRepository::recordStatistics);

    connect(ctrl, &IChoiceExerciseController::setDescription,
            w, &ExerciseNoTilesWidget::setDescription);

    connect(ctrl, &IChoiceExerciseController::replayAvailable,
            w, &ExerciseNoTilesWidget::onReplayAvailable);

    connect(w, &ExerciseNoTilesWidget::langChange,
            ctrl, &IChoiceExerciseController::retranslate);

    connect(ctrl, &IChoiceExerciseController::error,
            w, &ExerciseNoTilesWidget::showErrorInfo);

    ctrl->giveAnswers();
    ctrl->sendDescription();
}
