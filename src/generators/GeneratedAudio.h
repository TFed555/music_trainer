#ifndef GENERATEDAUDIO_H
#define GENERATEDAUDIO_H

#include <QVector>
#include "../music/musicutils.h"

struct GeneratedAudio {
    QString desc;
    QVector<int> midiNotes;
    QString direction;
};

struct GeneratedInterval : GeneratedAudio {
    QString interval;
    MusicUtils::Intervals::IntervalDirection direction;
};

struct GeneratedChord : GeneratedAudio {
    QString chordName;
    QString type;
    QString inversion;
    QString root;
};


#endif // GENERATEDAUDIO_H
