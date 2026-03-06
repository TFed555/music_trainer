#ifndef GENERATEDAUDIO_H
#define GENERATEDAUDIO_H

#include <QVector>

enum class IntervalDirection {
    Ascending,
    Descending
};

struct GeneratedAudio {
    QString desc;
    QString interval;
    IntervalDirection direction;
    QVector<int> midiNotes;
};

#endif // GENERATEDAUDIO_H
