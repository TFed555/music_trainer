#include "chordbuildsession.h"
#include "../core/controllers/common/tilescontroller.h"

ChordBuildSession::ChordBuildSession(NotePlayer* player,
                                           QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new ChordBuildController(player, this);
    view = new ExerciseWithTilesWidget(nullptr);

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &ChordBuildController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &ChordBuildController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &ChordBuildController::showResult,
            view, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &ChordBuildController::requestSetMode,
            view, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &ChordBuildController::noteSelected);

    connect(exerciseController, &ChordBuildController::exercisePlayFinished,
            view, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(exerciseController, &ChordBuildController::setQuestion,
            view, &ExerciseWithTilesWidget::setQuestion);

    connect(exerciseController, &ChordBuildController::highlightQuestion,
            view, &ExerciseWithTilesWidget::highlightQuestion);
}
