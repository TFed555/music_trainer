#include "intervalbuildsession.h"
#include "../core/controllers/common/tilescontroller.h"

IntervalBuildSession::IntervalBuildSession(NotePlayer* player,
                                           QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new IntervalBuildController(player, this);
    tilesView = new ExerciseWithTilesWidget(true, nullptr);
    view = tilesView;

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &IntervalBuildController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &IntervalBuildController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &IntervalBuildController::showResult,
            tilesView, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &IntervalBuildController::requestSetMode,
            tilesView, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &IntervalBuildController::noteSelected);

    connect(exerciseController, &IntervalBuildController::exercisePlayFinished,
            tilesView, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(exerciseController, &IntervalBuildController::setQuestion,
            tilesView, &ExerciseWithTilesWidget::setQuestion);

    connect(exerciseController, &IntervalBuildController::highlightQuestion,
            tilesView, &ExerciseWithTilesWidget::highlightQuestion);

    connect(tilesView, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &IntervalBuildController::setDifficulty);
}
