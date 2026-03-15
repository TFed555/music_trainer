#include "chordidentifysession.h"

ChordIdentifySession::ChordIdentifySession(NotePlayer* player,
                                            QObject *parent)
    : ISession{parent}
{
    exerciseController = new ChordIdentifyController(player, this);
    noTilesView = new ExerciseNoTilesWidget(nullptr);
    view = noTilesView;

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &ChordIdentifyController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &ChordIdentifyController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &ChordIdentifyController::showResult,
            noTilesView, &ExerciseNoTilesWidget::showResult);

    connect(noTilesView, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &ChordIdentifyController::answerSelected);

    connect(exerciseController, &ChordIdentifyController::setAnswers,
            noTilesView, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &ChordIdentifyController::exercisePlayFinished,
            noTilesView, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(noTilesView, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &ChordIdentifyController::setDifficulty);

    exerciseController->giveAnswers();
}
