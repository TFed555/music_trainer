#ifndef EXERCISERHYTHMWIDGET_H
#define EXERCISERHYTHMWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../../music/musicutils.h"
#include "../common/rhythmcanvaswidget.h"
#include <QLabel>
#include <QCheckBox>

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
    void setDescription(const QString& text) override;
    void setMode(Mode m);
signals:
    void inputFinished(const QVector<int>& notePoses, const QVector<int>& userTaps);
    void configChanged(const QMap<int,int>& states);
    void bpmChanged(const int &bpm);
protected:
    void keyPressEvent(QKeyEvent* event) override;
private:
    void retranslate() override;
    Ui::ExerciseRhythmWidget *ui;
    RhythmCanvasWidget* canvas;
    QMap<int,int> states = {
        {1, 0},
        {2, 0},
        {4, 1},
        {8, 0},
        {16, 0},
    };
    QLabel* descriptionLabel = nullptr;
    QVector<QString> durationNames() const {
        return MusicUtils::toNameVector(MusicUtils::Rhythm::allDurations,
                                        MusicUtils::Rhythm::durationName);
    }
};

#endif // EXERCISERHYTHMWIDGET_H
