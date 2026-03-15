#include "chordbuildsession.h"
#include "../core/controllers/common/tilescontroller.h"

ChordBuildSession::ChordBuildSession(NotePlayer* player,
                                           QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new ChordBuildController(player, this);
    tilesView = new ExerciseWithTilesWidget(true, nullptr);
    view = tilesView;

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &ChordBuildController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &ChordBuildController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &ChordBuildController::showResult,
            tilesView, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &ChordBuildController::requestSetMode,
            tilesView, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &ChordBuildController::noteSelected);

    connect(exerciseController, &ChordBuildController::exercisePlayFinished,
            tilesView, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(exerciseController, &ChordBuildController::setQuestion,
            tilesView, &ExerciseWithTilesWidget::setQuestion);

    connect(exerciseController, &ChordBuildController::highlightQuestion,
            tilesView, &ExerciseWithTilesWidget::highlightQuestion);

    connect(tilesView, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &ChordBuildController::setDifficulty);
}
