#ifndef INTERVALGENERATOR_H
#define INTERVALGENERATOR_H
#pragma once

#include "../IGenerator.h"
#include "../core/common/models/Difficulty.h"
#include <random>

class IntervalGenerator : public IGenerator<IntervalGenerator, GeneratedInterval> {
public:
    explicit IntervalGenerator(IntervalDifficultyConfig config = {});
    GeneratedInterval generate();
private:
    std::mt19937 gen{std::random_device{}()};
    IntervalDifficultyConfig config;
};

#endif // INTERVALGENERATOR_H
