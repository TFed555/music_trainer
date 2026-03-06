#ifndef INTERVALGENERATOR_H
#define INTERVALGENERATOR_H
#pragma once

#include "../IGenerator.h"

class IntervalGenerator : public IGenerator<GeneratedInterval> {
public:
    GeneratedInterval generate() override;
};

#endif // INTERVALGENERATOR_H
