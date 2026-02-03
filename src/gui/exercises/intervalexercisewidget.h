#ifndef INTERVALEXERCISEWIDGET_H
#define INTERVALEXERCISEWIDGET_H

#include <QWidget>
#include "../../audio/audio.h"

namespace Ui {
class IntervalExerciseWidget;
}

class IntervalExerciseWidget : public QWidget //переделать на наследуемый
{
    Q_OBJECT

public:
    explicit IntervalExerciseWidget(QWidget *parent = nullptr);
    ~IntervalExerciseWidget();

    void playTone();

private:
    Ui::IntervalExerciseWidget *ui;
    AudioProcessor *processor;
};

#endif // INTERVALEXERCISEWIDGET_H
