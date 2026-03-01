#ifndef INTERVALIDENTIFYCONTROLLER_H
#define INTERVALIDENTIFYCONTROLLER_H

#include <QObject>
#include "iexercisecontroller.h"

class IntervalIdentifyController : public IExerciseController
{
public:
    explicit IntervalIdentifyController(NotePlayer* player);
public slots:
    void start() override;
    void stop() override;
private:
};

#endif // INTERVALIDENTIFYCONTROLLER_H
