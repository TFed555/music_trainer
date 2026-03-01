#include "intervalidentifysession.h"

IntervalIdentifySession::IntervalIdentifySession(QWidget* parentWidget,
                                                   NotePlayer* player,
                                                   QObject* parent)
    : ISession(parent)
{
    exerciseController = new IntervalIdentifyController(player);
    view = new ExerciseNoTilesWidget(parentWidget);

    connect(view, &ExerciseNoTilesWidget::startClicked, exerciseController, &IntervalIdentifyController::start);

    connect(view, &ExerciseNoTilesWidget::stopClicked, exerciseController, &IntervalIdentifyController::stop);

    connect(view, &ExerciseNoTilesWidget::backClicked, this, [this](){
        emit back();
    });

    // connect(exerciseController, &IntervalIdentifyController::showResult,
    //         view, &ExerciseNoTilesWidget::showResult);

    connect(view, &ExerciseNoTilesWidget::answerSelected,
            exerciseController, &IntervalIdentifyController::answerSelected);

    connect(view, &ExerciseNoTilesWidget::requestAnswers,
            exerciseController, &IntervalIdentifyController::giveAnswers);

    connect(exerciseController, &IntervalIdentifyController::setAnswers,
            view, &ExerciseNoTilesWidget::addAnswers);

    view->requestAnswerSlot();
}
