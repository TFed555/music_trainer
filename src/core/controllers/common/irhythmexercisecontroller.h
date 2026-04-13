#ifndef IRHYTHMEXERCISECONTROLLER_H
#define IRHYTHMEXERCISECONTROLLER_H

#include "iexercisecontroller.h"
#include "../../common/models/Mode.h"

class IRhythmExerciseController : public IExerciseController
{
    Q_OBJECT
public:
    using IExerciseController::IExerciseController;
public slots:
    virtual void inputFinished(const QVector<int>& notePoses,
                               const QVector<int>& userTaps) = 0;
    virtual void setConfig(const QMap<int,int>& states) = 0;
    virtual void bpmChanged(const int& bpm) = 0;
signals:
    void setRhythmNotes(const QVector<MusicUtils::Rhythm::RhythmType>&, int bpm);
    void showResult(int correct, int wrong);
    void attemptDone(RhythmAttempt);
    void requestSetMode(Mode);
};

#endif // IRHYTHMEXERCISECONTROLLER_H
