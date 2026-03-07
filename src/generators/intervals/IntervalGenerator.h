#ifndef INTERVALGENERATOR_H
#define INTERVALGENERATOR_H
#pragma once

#include "../IGenerator.h"
#include <random>

class IntervalGenerator : public IGenerator<GeneratedInterval> {
public:
    GeneratedInterval generate() override;
private:
    std::random_device rd;
    std::mt19937 gen{std::random_device{}()};
};

#endif // INTERVALGENERATOR_H
