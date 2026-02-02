#ifndef IGENERATOR_H
#define IGENERATOR_H
#pragma once
#include "GeneratedAudio.h"

class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual GeneratedAudio generate(int sampleRate, float durationSec) = 0;
};

#endif
