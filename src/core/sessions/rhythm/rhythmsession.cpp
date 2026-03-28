#include "rhythmsession.h"

void RhythmSession::setup(IRhythmExerciseController* ctrl, ExerciseRhythmWidget* w) {
    view = w;

    connect(view, &ExerciseRhythmWidget::startClicked, ctrl, &IRhythmExerciseController::start);

    connect(view, &ExerciseRhythmWidget::stopClicked, ctrl, &IRhythmExerciseController::stop);

    connect(view, &ExerciseRhythmWidget::backClicked, this, [this](){
        emit back();
    });

    connect(ctrl, &IRhythmExerciseController::setRhythmNotes,
            w, &ExerciseRhythmWidget::setRhythmNotes);

    connect(ctrl, &IRhythmExerciseController::exercisePlayFinished,
            w, &ExerciseRhythmWidget::exercisePlayFinished);

    connect(w, &ExerciseRhythmWidget::inputFinished, ctrl,
                &IRhythmExerciseController::inputFinished);

    connect(ctrl, &IRhythmExerciseController::result,
            w, &ExerciseRhythmWidget::getResult);

    connect(w, &ExerciseRhythmWidget::configChanged,
            ctrl, &IRhythmExerciseController::setConfig);

    connect(w, &ExerciseRhythmWidget::bpmChanged,
            ctrl, &IRhythmExerciseController::bpmChanged);
}
