#include "intervalbuildsession.h"
#include "../core/controllers/tilescontroller.h"

IntervalBuildSession::IntervalBuildSession(QWidget* parentWidget,
                                           NotePlayer* player,
                                           QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new IntervalBuildController(player);
    view = new ExerciseWithTilesWidget(parentWidget);

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &IntervalBuildController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &IntervalBuildController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &IntervalBuildController::showResult,
            view, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &IntervalBuildController::requestSetMode,
            view, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &IntervalBuildController::noteSelected);

    connect(exerciseController, &IntervalBuildController::exercisePlayFinished,
            view, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(exerciseController, &IntervalBuildController::setQuestion,
            view, &ExerciseWithTilesWidget::setQuestion);

    connect(exerciseController, &IntervalBuildController::highlightQuestion,
            view, &ExerciseWithTilesWidget::highlightQuestion);


}
