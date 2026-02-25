#include "sampleloader.h"
#include <QDebug>

SampleLoader::SampleLoader() {}

SampleLoader::~SampleLoader() {}

Sample SampleLoader::loadSample(const char *path, int midi) {
    SF_INFO sfInfo;
    sfInfo.format = 0;
    SNDFILE* file = sf_open(path, SFM_READ, &sfInfo);

    if (!file) {
        throw std::runtime_error("Не удается открыть сэмпл");
    }

    QVector<float> data;

    data.resize(sfInfo.frames * sfInfo.channels);

    sf_count_t frames = sf_readf_float(file, data.data(), sfInfo.frames);

    if (frames != sfInfo.frames) {
        qDebug() << "..";
    }

    Sample sample;
    sample.data = data;
    sample.nearestMidi = midi;
    sample.sampleRate = 44100;

    sf_close(file);

    return sample;
}
