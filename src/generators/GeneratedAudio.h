#ifndef GENERATEDAUDIO_H
#define GENERATEDAUDIO_H

#include <QVector>

enum class IntervalDirection {
    Ascending,
    Descending
};

struct GeneratedAudio {
    QString desc;
    QVector<int> midiNotes;
};

struct GeneratedInterval : GeneratedAudio {
    QString interval;
    IntervalDirection direction;
};

struct GeneratedChord : GeneratedAudio {
    QString chordName;
    // QString quality;
    QString tone;
};

#endif // GENERATEDAUDIO_H
