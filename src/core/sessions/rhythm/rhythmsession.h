#ifndef RHYTHMSESSION_H
#define RHYTHMSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exerciserhythmwidget.h"
#include "../core/controllers/common/irhythmexercisecontroller.h"

class RhythmSession : public ISession
{
    Q_OBJECT
public:
    explicit RhythmSession(const QString& sessionTitle,
                            QObject* parent = nullptr)
        : ISession(parent), _title(sessionTitle) {

    };

    void setup(IRhythmExerciseController* ctrl, ExerciseRhythmWidget* w);
    QString title() const override { return _title;}

private:
    QString _title;
};

#endif // RHYTHMSESSION_H
