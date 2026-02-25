#ifndef SAMPLE_H
#define SAMPLE_H

#include <QVector>

struct Sample {
    QVector<float> data;
    int nearestMidi;
    int sampleRate;
};


#endif // SAMPLE_H
