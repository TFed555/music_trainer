#ifndef SAMPLEREPOSITORY_H
#define SAMPLEREPOSITORY_H

#include "sample.h"
#include "sampleloader.h"

class SampleRepository
{
public:
    explicit SampleRepository(SampleLoader* loader = nullptr);

    Sample getSample(int midi);
    Sample getBeatSample();
private:
    SampleLoader* loader;
};

#endif // SAMPLEREPOSITORY_H
