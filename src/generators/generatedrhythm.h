#ifndef GENERATEDRHYTHM_H
#define GENERATEDRHYTHM_H

#include <QVector>
#include "../music/pitchutils.h"

struct Beat {
    MusicUtils::Rhythm::BeatType type;
    int duration;
};

struct GeneratedRhythm {
    QVector<Beat> beats;
    int bpm;
    QString desc;
};

#endif // GENERATEDRHYTHM_H
