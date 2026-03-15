#include "chordrootsession.h"
#include "../core/controllers/common/tilescontroller.h"

ChordRootSession::ChordRootSession(NotePlayer* player,
                                   QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new ChordRootController(player, this);
    tilesView = new ExerciseWithTilesWidget(true, nullptr);
    view = tilesView;

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &ChordRootController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &ChordRootController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect (exerciseController, &ChordRootController::showResult,
            tilesView, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &ChordRootController::requestSetMode,
            tilesView, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &ChordRootController::noteSelected);

    connect(exerciseController, &ChordRootController::exercisePlayFinished,
            tilesView, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(tilesView, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &ChordRootController::setDifficulty);

}
