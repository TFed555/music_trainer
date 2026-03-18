#include "rhythmrecognisecontroller.h"
#include "../../generators/rhythm/rhythmgenerator.h"

RhythmRecogniseController::RhythmRecogniseController(NotePlayer* player,
                                                     QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{

}

void RhythmRecogniseController::playTone() {
    RhythmGenerator generator(config);
    auto result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playBeat(result);
}

void RhythmRecogniseController::setDifficulty(int level) {

}
