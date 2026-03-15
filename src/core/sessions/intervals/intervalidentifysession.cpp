#include "intervalidentifysession.h"

IntervalIdentifySession::IntervalIdentifySession(NotePlayer* player,
                                                   QObject* parent)
    : ISession(parent)
{
    exerciseController = new IntervalIdentifyController(player, this);
    noTilesView = new ExerciseNoTilesWidget(nullptr);
    view = noTilesView;

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &IntervalIdentifyController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &IntervalIdentifyController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &IntervalIdentifyController::showResult,
            noTilesView, &ExerciseNoTilesWidget::showResult);

    connect(noTilesView, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &IntervalIdentifyController::answerSelected);

    connect(exerciseController, &IntervalIdentifyController::setAnswers,
            noTilesView, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &IntervalIdentifyController::exercisePlayFinished,
            noTilesView, &ExerciseNoTilesWidget::exercisePlayFinished);

    connect(noTilesView, &ExerciseNoTilesWidget::difficultyChanged,
            exerciseController, &IntervalIdentifyController::setDifficulty);

    exerciseController->giveAnswers();
}
