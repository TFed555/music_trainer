#include "intervalrecognisewidget.h"

IntervalRecogniseWidget::IntervalRecogniseWidget(QObject *parent)
    : IntervalExerciseWidget(this)
{
    widget = new IntervalExerciseWidget(this);
    controller = new IntervalRecogniseController();

    connect(widget, &IntervalExerciseWidget::start, controller, &IntervalRecogniseController::start);

    connect(widget, &IntervalExerciseWidget::stop, controller, &IntervalRecogniseController::stop);

    // connect(widget, &IntervalExerciseWidget::backClicked, );
}
