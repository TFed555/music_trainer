#include "intervalrecognisesession.h"
#include "../core/controllers/tilescontroller.h"

IntervalRecogniseSession::IntervalRecogniseSession(QWidget* parentWidget,
                                                   NotePlayer* player,
                                                   QObject* parent)
    : ISession(parent)
{
    view = new IntervalExerciseWidget(parentWidget);
    auto* tilesController = new TilesController(player);
    exerciseController = new IntervalRecogniseController(player);

    connect(view, &IntervalExerciseWidget::startClicked, exerciseController, &IntervalRecogniseController::start);

    connect(view, &IntervalExerciseWidget::stopClicked, exerciseController, &IntervalRecogniseController::stop);

    connect(view, &IntervalExerciseWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &IntervalRecogniseController::showResult,
            view, &IntervalExerciseWidget::showResult);

    connect(exerciseController, &IntervalRecogniseController::requestSetMode,
            view, &IntervalExerciseWidget::setMode, Qt::QueuedConnection);

    connect(view, &IntervalExerciseWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &IntervalExerciseWidget::noteSelected,
            exerciseController, &IntervalRecogniseController::noteSelected);

}
