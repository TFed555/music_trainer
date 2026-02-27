#ifndef INTERVALRECOGNISECONTROLLER_H
#define INTERVALRECOGNISECONTROLLER_H

#include "iexercisecontroller.h"

class IntervalRecogniseController : public IExerciseController
{
public:
    explicit IntervalRecogniseController();

    void start() override;
    void stop() override;

private:
    NotePlayer* notePlayer;
};

#endif // INTERVALRECOGNISECONTROLLER_H
