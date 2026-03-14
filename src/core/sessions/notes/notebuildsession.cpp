#include "notebuildsession.h"
#include "../core/controllers/common/tilescontroller.h"

NoteBuildSession::NoteBuildSession(NotePlayer* player,
                                   QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new NoteBuildController(player, this);
    view = new ExerciseWithTilesWidget(false, nullptr);

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &NoteBuildController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &NoteBuildController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &NoteBuildController::showResult,
            view, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &NoteBuildController::requestSetMode,
            view, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &NoteBuildController::noteSelected);

    connect(exerciseController, &NoteBuildController::exercisePlayFinished,
            view, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(exerciseController, &NoteBuildController::setQuestion,
            view, &ExerciseWithTilesWidget::setQuestion);

    connect(view, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &NoteBuildController::setDifficulty);

    connect(exerciseController, &NoteBuildController::setOctaveCount,
            view, &ExerciseWithTilesWidget::setOctaveCount);

    exerciseController->setDifficulty(0);
}
