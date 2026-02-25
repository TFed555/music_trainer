#ifndef SAMPLELOADER_H
#define SAMPLELOADER_H

#include "sample.h"
#include "sndfile.h"

class SampleLoader
{
public:
    explicit SampleLoader();
    ~SampleLoader();
    Sample loadSample(const char *path, int midi);
};

#endif // SAMPLELOADER_H
