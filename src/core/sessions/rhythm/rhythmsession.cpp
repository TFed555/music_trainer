#include "rhythmsession.h"

void RhythmSession::setup(IRhythmExerciseController* ctrl, ExerciseRhythmWidget* w) {
    view = w;

    connect(view, &ExerciseRhythmWidget::startClicked, ctrl, &IRhythmExerciseController::start);

    connect(view, &ExerciseRhythmWidget::stopClicked, ctrl, &IRhythmExerciseController::stop);

    connect(view, &ExerciseRhythmWidget::backClicked, this, [this](){
        emit back();
    });

    connect(w, &ExerciseRhythmWidget::replayClicked, ctrl, &IRhythmExerciseController::replay);

    connect(ctrl, &IRhythmExerciseController::setRhythmNotes,
            w, &ExerciseRhythmWidget::setRhythmNotes);

    connect(ctrl, &IRhythmExerciseController::requestSetMode,
            w, &ExerciseRhythmWidget::setMode, Qt::QueuedConnection);

    connect(ctrl, &IRhythmExerciseController::exercisePlayFinished,
            w, &ExerciseRhythmWidget::exercisePlayFinished);

    connect(w, &ExerciseRhythmWidget::inputFinished, ctrl,
                &IRhythmExerciseController::inputFinished);

    connect(ctrl, &IRhythmExerciseController::showResult,
            w, &ExerciseRhythmWidget::getResult);

    connect(w, &ExerciseRhythmWidget::configChanged,
            ctrl, &IRhythmExerciseController::setConfig);

    connect(w, &ExerciseRhythmWidget::bpmChanged,
            ctrl, &IRhythmExerciseController::bpmChanged);

    connect(ctrl, &IRhythmExerciseController::setDescription,
            w, &ExerciseRhythmWidget::setDescription);

    connect(w, &ExerciseRhythmWidget::langChange,
            ctrl, &IRhythmExerciseController::retranslate);

    connect(ctrl, &IRhythmExerciseController::error,
            w, &ExerciseRhythmWidget::showErrorInfo);

    ctrl->sendDescription();
}
