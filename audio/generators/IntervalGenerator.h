#ifndef INTERVALGENERATOR_H
#define INTERVALGENERATOR_H
#pragma once

#include "IGenerator.h"

class IntervalGenerator : public IGenerator {
public:
    GeneratedAudio generate(int sampleRate, float durationSec) override;
};

#endif // INTERVALGENERATOR_H
