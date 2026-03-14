#include "intervalidentifysession.h"

IntervalIdentifySession::IntervalIdentifySession(NotePlayer* player,
                                                   QObject* parent)
    : ISession(parent)
{
    exerciseController = new IntervalIdentifyController(player, this);
    view = new ExerciseNoTilesWidget(nullptr);

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &IntervalIdentifyController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &IntervalIdentifyController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &IntervalIdentifyController::showResult,
            view, &ExerciseNoTilesWidget::showResult);

    connect(view, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &IntervalIdentifyController::answerSelected);

    connect(exerciseController, &IntervalIdentifyController::setAnswers,
            view, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &IntervalIdentifyController::exercisePlayFinished,
            view, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(view, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &IntervalIdentifyController::setDifficulty);

    exerciseController->giveAnswers();
}
