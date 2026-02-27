#ifndef INTERVALRECOGNISECONTROLLER_H
#define INTERVALRECOGNISECONTROLLER_H

#include "iexercisecontroller.h"
#include "../../audio/playback/noteplayer.h"

class IntervalRecogniseController : public IExerciseController
{
public:
    IntervalRecogniseController();

    void start() override;
    void stop() override;

private:
    NotePlayer* notePlayer;
};

#endif // INTERVALRECOGNISECONTROLLER_H
