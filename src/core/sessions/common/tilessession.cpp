#include "tilessession.h"

void TilesSession::setup(ITilesExerciseController* ctrl, TilesController* tilesctrl,
                         ExerciseWithTilesWidget* w, StatisticsRepository* statsRepo) {
    view = w;
    connect(view, &ExerciseWithTilesWidget::startClicked, ctrl, &ITilesExerciseController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, ctrl, &ITilesExerciseController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(w, &ExerciseWithTilesWidget::replayClicked, ctrl, &ITilesExerciseController::replay);

    connect (ctrl, &ITilesExerciseController::showResult,
            w, &ExerciseWithTilesWidget::showResult);

    connect(ctrl, &ITilesExerciseController::requestSetMode,
            w, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(w, &ExerciseWithTilesWidget::noteSelected,
            tilesctrl, [tilesctrl](const QString& noteName){
                tilesctrl->playTile(noteName);
            });

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

    connect(ctrl, &ITilesExerciseController::attemptDone,
                    statsRepo, &StatisticsRepository::recordStatistics);

    connect(ctrl, &ITilesExerciseController::setDescription,
            w, &ExerciseWithTilesWidget::setDescription);

    connect(ctrl, &ITilesExerciseController::setOctaveCount,
            w, &ExerciseWithTilesWidget::setOctaveCount);

    connect(ctrl, &ITilesExerciseController::replayAvailable,
            w, &ExerciseWithTilesWidget::onReplayAvailable);

    connect(w, &ExerciseWithTilesWidget::langChange,
            ctrl, &ITilesExerciseController::retranslate);

    connect(ctrl, &ITilesExerciseController::error,
            w, &ExerciseWithTilesWidget::showErrorInfo);

    ctrl->sendDescription();
    ctrl->setDifficulty(0);
}
