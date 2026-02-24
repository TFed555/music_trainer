#include "sampleloader.h"

SampleLoader::SampleLoader() {}

Sample SampleLoader::loadSample(QString path, int midi) {
    SF_INFO sfInfo;
    sfInfo.format = 0;
    SNDFILE* file = sf_open("../../../assets/samples/C4v14.wav", SFM_READ, &sfInfo);

    QVector<float> data;

    data.resize(sfInfo.frames * sfInfo.channels);

    sf_count_t frames = sf_read_float(file, data.data(), sfInfo.frames);

    Sample sample;
    sample.data = data;
    sample.sampleRate = 44100;

    return sample;
}
