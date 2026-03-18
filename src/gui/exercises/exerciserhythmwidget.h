#ifndef EXERCISERHYTHMWIDGET_H
#define EXERCISERHYTHMWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include <QKeyEvent>

namespace Ui {
class ExerciseRhythmWidget;
}

class ExerciseRhythmWidget : public IExerciseWidget
{
    Q_OBJECT

public:
    explicit ExerciseRhythmWidget(QWidget *parent = nullptr);
    ~ExerciseRhythmWidget();
public slots:
    void exercisePlayFinished() override;
private:
    void keyPressEvent(QKeyEvent* event) override;
private:
    Ui::ExerciseRhythmWidget *ui;
};

#endif // EXERCISERHYTHMWIDGET_H
