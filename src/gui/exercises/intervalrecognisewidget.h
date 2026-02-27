#ifndef INTERVALRECOGNISEWIDGET_H
#define INTERVALRECOGNISEWIDGET_H

#include "intervalexercisewidget.h"
#include "../core/controllers/intervalrecognisecontroller.h"

class IntervalRecogniseWidget : public IntervalExerciseWidget
{
    Q_OBJECT
public:
    explicit IntervalRecogniseWidget(QObject *parent = nullptr);
private:
    IntervalExerciseWidget* widget;
    IntervalRecogniseController* controller;
    int noteCounter = 0;
};

#endif // INTERVALRECOGNISEWIDGET_H
