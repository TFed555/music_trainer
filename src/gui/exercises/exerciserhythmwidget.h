#ifndef EXERCISERHYTHMWIDGET_H
#define EXERCISERHYTHMWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../../music/pitchutils.h"
#include "../common/rhythmcanvaswidget.h"
// #include "../../core/common/models/Rhythm.h"

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
    void setRhythmNotes(const QVector<MusicUtils::Rhythm::RhythmType>& notes, int bpm);
    void getResult(const int correct, const int wrong);
signals:
    void inputFinished(const QVector<int>& notePoses, const QVector<int>& userTaps);
private:
    Ui::ExerciseRhythmWidget *ui;
    RhythmCanvasWidget* canvas;
};

#endif // EXERCISERHYTHMWIDGET_H
