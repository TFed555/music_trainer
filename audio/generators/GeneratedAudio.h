#ifndef GENERATEDAUDIO_H
#define GENERATEDAUDIO_H

#include <QVector>

struct GeneratedAudio {
    QVector<float> samples;
    QString desc;
    QVector<int> midiNotes;
};

#endif // GENERATEDAUDIO_H
