#include "chordrootsession.h"
#include "../core/controllers/common/tilescontroller.h"

ChordRootSession::ChordRootSession(NotePlayer* player,
                                   QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new ChordRootController(player, this);
    view = new ExerciseWithTilesWidget(nullptr);

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &ChordRootController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &ChordRootController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect (exerciseController, &ChordRootController::showResult,
            view, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &ChordRootController::requestSetMode,
            view, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &ChordRootController::noteSelected);

    connect(exerciseController, &ChordRootController::exercisePlayFinished,
            view, &ExerciseWithTilesWidget::exercisePlayFinished);
}
