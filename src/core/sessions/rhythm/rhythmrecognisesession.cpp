#include "rhythmrecognisesession.h"

RhythmRecogniseSession::RhythmRecogniseSession(NotePlayer* player,
                                               QObject* parent)
    : ISession(parent)
{
    exerciseController = new RhythmRecogniseController(player, this);
    rhythmView = new ExerciseRhythmWidget(nullptr);
    view = rhythmView;

    connect(view, &ExerciseRhythmWidget::startClicked, exerciseController, &RhythmRecogniseController::start);

    connect(view, &ExerciseRhythmWidget::stopClicked, exerciseController, &RhythmRecogniseController::stop);

    connect(view, &ExerciseRhythmWidget::backClicked, this, [this](){
        emit back();
    });

    connect(exerciseController, &RhythmRecogniseController::setRhythmNotes,
            rhythmView, &ExerciseRhythmWidget::setRhythmNotes);

    // connect(exerciseController, &NoteGuessController::showResult,
    //         noTilesView, &ExerciseNoTilesWidget::showResult);

    // connect(noTilesView, &ExerciseNoTilesWidget::answerSelected,
    //         exerciseController, &NoteGuessController::answerSelected);

    // connect(exerciseController, &NoteGuessController::setAnswers,
    //         noTilesView, &ExerciseNoTilesWidget::addAnswers);

    connect(exerciseController, &RhythmRecogniseController::exercisePlayFinished,
            rhythmView, &ExerciseRhythmWidget::exercisePlayFinished);

    connect(rhythmView, &ExerciseRhythmWidget::inputFinished, exerciseController,
                &RhythmRecogniseController::inputFinished);

    connect(exerciseController, &RhythmRecogniseController::result,
            rhythmView, &ExerciseRhythmWidget::getResult);

    connect(rhythmView, &ExerciseRhythmWidget::difficultyChanged,
            exerciseController, &RhythmRecogniseController::setDifficulty);
}
