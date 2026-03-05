#include "intervalrecognisesession.h"
#include "../core/controllers/tilescontroller.h"

IntervalRecogniseSession::IntervalRecogniseSession(NotePlayer* player,
                                                   QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new IntervalRecogniseController(player, this);
    view = new ExerciseWithTilesWidget(nullptr);

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &IntervalRecogniseController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &IntervalRecogniseController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect (exerciseController, &IntervalRecogniseController::showResult,
            view, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &IntervalRecogniseController::requestSetMode,
            view, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &IntervalRecogniseController::noteSelected);

    connect(exerciseController, &IntervalRecogniseController::exercisePlayFinished,
            view, &ExerciseWithTilesWidget::exercisePlayFinished);
}
