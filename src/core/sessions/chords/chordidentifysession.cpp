#include "chordidentifysession.h"

ChordIdentifySession::ChordIdentifySession(NotePlayer* player,
                                            QObject *parent)
    : ISession{parent}
{
    exerciseController = new ChordIdentifyController(player, this);
    view = new ExerciseNoTilesWidget(nullptr);

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &ChordIdentifyController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &ChordIdentifyController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &ChordIdentifyController::showResult,
            view, &ExerciseNoTilesWidget::showResult);

    connect(view, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &ChordIdentifyController::answerSelected);

    connect(exerciseController, &ChordIdentifyController::setAnswers,
            view, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &ChordIdentifyController::exercisePlayFinished,
            view, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(view, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &ChordIdentifyController::setDifficulty);

    exerciseController->giveAnswers();
}
