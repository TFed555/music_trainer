#include "rhythmrecognisecontroller.h"
#include "../../generators/rhythm/rhythmgenerator.h"


RhythmRecogniseController::RhythmRecogniseController(NotePlayer* player,
                                                     QObject *parent)
    : IExerciseController(player, PlaybackendSignal::PlaylistEmpty, parent)
{
}

void RhythmRecogniseController::playTone() {
    using namespace MusicUtils::Rhythm;
    RhythmGenerator generator(config);
    auto result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playBeat(result);
    QVector<RhythmType> rhythmTypes;
    for (auto b : result.beats) {
        rhythmTypes.append(rhythmTypeNames[b.duration]);
    }
    setRhythmNotes(rhythmTypes);
}

void RhythmRecogniseController::setDifficulty(int level) {

}

