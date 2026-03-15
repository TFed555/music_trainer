#include "intervalrecognisesession.h"
#include "../core/controllers/common/tilescontroller.h"

IntervalRecogniseSession::IntervalRecogniseSession(NotePlayer* player,
                                                   QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new IntervalRecogniseController(player, this);
    tilesView = new ExerciseWithTilesWidget(true, nullptr);
    view = tilesView;

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &IntervalRecogniseController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &IntervalRecogniseController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect (exerciseController, &IntervalRecogniseController::showResult,
            tilesView, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &IntervalRecogniseController::requestSetMode,
            tilesView, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &IntervalRecogniseController::noteSelected);

    connect(exerciseController, &IntervalRecogniseController::exercisePlayFinished,
            tilesView, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(tilesView, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &IntervalRecogniseController::setDifficulty);
}
