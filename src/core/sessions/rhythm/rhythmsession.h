#ifndef RHYTHMSESSION_H
#define RHYTHMSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exerciserhythmwidget.h"
#include "../core/controllers/common/irhythmexercisecontroller.h"

class RhythmSession : public ISession
{
    Q_OBJECT
public:
    explicit RhythmSession(ExerciseType type,
                            QObject* parent = nullptr)
        : ISession(type, parent){

    };

    void setup(IRhythmExerciseController* ctrl, ExerciseRhythmWidget* w);
};

#endif // RHYTHMSESSION_H
