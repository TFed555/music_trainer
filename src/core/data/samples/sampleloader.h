#ifndef SAMPLELOADER_H
#define SAMPLELOADER_H

#include "sample.h"
#include "sndfile.h"

class SampleLoader
{
public:
    explicit SampleLoader();
    Sample loadSample(QString path, int midi);
};

#endif // SAMPLELOADER_H
