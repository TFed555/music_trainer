#ifndef GENERATEDRHYTHM_H
#define GENERATEDRHYTHM_H

#include <QVector>
#include "../music/musicutils.h"

struct Beat {
    MusicUtils::Rhythm::BeatType type;
    int duration;
};

struct GeneratedRhythm {
    QVector<Beat> userBeats;
    QVector<Beat> metronomeBeats;
    int bpm;
    QString desc;
};

#endif // GENERATEDRHYTHM_H
