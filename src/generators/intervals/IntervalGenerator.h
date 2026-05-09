#ifndef INTERVALGENERATOR_H
#define INTERVALGENERATOR_H
#pragma once

#include "../GeneratedAudio.h"
#include "../IGenerator.h"
#include "../core/common/models/Difficulty.h"
#include <random>

class IntervalGenerator : public IGenerator<IntervalGenerator, GeneratedInterval> {
    friend class IGenerator<IntervalGenerator, GeneratedInterval>;
public:
    explicit IntervalGenerator(IntervalDifficultyConfig config = {});
    // GeneratedInterval generate();
protected:
    GeneratedInterval doGenerate() override;
private:
    std::mt19937 gen{std::random_device{}()};
    IntervalDifficultyConfig config;
};

#endif // INTERVALGENERATOR_H
