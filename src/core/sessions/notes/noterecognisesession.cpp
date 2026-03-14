#include "noterecognisesession.h"
#include "../core/controllers/common/tilescontroller.h"

NoteRecogniseSession::NoteRecogniseSession(NotePlayer* player,
                                           QObject* parent)
    : ISession(parent)
{
    auto* tilesController = new TilesController(player, this);
    exerciseController = new NoteRecogniseController(player, this);
    view = new ExerciseWithTilesWidget(true, nullptr);

    connect(view, &ExerciseWithTilesWidget::startClicked, exerciseController, &NoteRecogniseController::start);

    connect(view, &ExerciseWithTilesWidget::stopClicked, exerciseController, &NoteRecogniseController::stop);

    connect(view, &ExerciseWithTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect (exerciseController, &NoteRecogniseController::showResult,
            view, &ExerciseWithTilesWidget::showResult);

    connect(exerciseController, &NoteRecogniseController::requestSetMode,
            view, &ExerciseWithTilesWidget::setMode, Qt::QueuedConnection);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            tilesController, &TilesController::playTile);

    connect(view, &ExerciseWithTilesWidget::noteSelected,
            exerciseController, &NoteRecogniseController::noteSelected);

    connect(exerciseController, &NoteRecogniseController::exercisePlayFinished,
            view, &ExerciseWithTilesWidget::exercisePlayFinished);

    connect(view, &ExerciseWithTilesWidget::difficultyChanged,
            exerciseController, &NoteRecogniseController::setDifficulty);
}
