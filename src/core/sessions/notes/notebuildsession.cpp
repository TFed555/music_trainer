#include "notebuildsession.h"
#include "../core/controllers/common/tilescontroller.h"

NoteBuildSession::NoteBuildSession(NotePlayer* player,
                                   QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new NoteBuildController(player, this);
    tilesView = new ExerciseWithTilesWidget(false, nullptr);
    view = tilesView;

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &NoteBuildController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &NoteBuildController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &NoteBuildController::showResult,
            tilesView, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &NoteBuildController::requestSetMode,
            tilesView, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &NoteBuildController::noteSelected);

    connect(exerciseController, &NoteBuildController::exercisePlayFinished,
            tilesView, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(exerciseController, &NoteBuildController::setQuestion,
            tilesView, &ExerciseWithTilesWidget::setQuestion);

    connect(tilesView, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &NoteBuildController::setDifficulty);

    connect(exerciseController, &NoteBuildController::setOctaveCount,
            tilesView, &ExerciseWithTilesWidget::setOctaveCount);

    exerciseController->setDifficulty(0);
}
