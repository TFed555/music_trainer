#include "noterecognisesession.h"
#include "../core/controllers/common/tilescontroller.h"

NoteRecogniseSession::NoteRecogniseSession(NotePlayer* player,
                                           QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new NoteRecogniseController(player, this);
    tilesView = new ExerciseWithTilesWidget(true, nullptr);
    view = tilesView;

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &NoteRecogniseController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &NoteRecogniseController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect (exerciseController, &NoteRecogniseController::showResult,
            tilesView, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &NoteRecogniseController::requestSetMode,
            tilesView, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(tilesView, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &NoteRecogniseController::noteSelected);

    connect(exerciseController, &NoteRecogniseController::exercisePlayFinished,
            tilesView, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(tilesView, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &NoteRecogniseController::setDifficulty);
}
