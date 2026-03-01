#include "intervalrecognisesession.h"
#include "../core/controllers/tilescontroller.h"

IntervalRecogniseSession::IntervalRecogniseSession(QWidget* parentWidget,
                                                   NotePlayer* player,
                                                   QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player);
    exerciseController = new IntervalRecogniseController(player);
    view = new ExerciseWithTilesWidget(parentWidget);

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &IntervalRecogniseController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &IntervalRecogniseController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &IntervalRecogniseController::showResult,
            view, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &IntervalRecogniseController::requestSetMode,
            view, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &IntervalRecogniseController::noteSelected);

}
