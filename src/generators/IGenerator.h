#ifndef IGENERATOR_H
#define IGENERATOR_H
#pragma once
#include "GeneratedAudio.h"

template <typename T>
class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual T generate() = 0;
};

#endif
