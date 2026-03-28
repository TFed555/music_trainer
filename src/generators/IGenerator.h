#ifndef IGENERATOR_H
#define IGENERATOR_H
#pragma once
#include "GeneratedAudio.h"

template <typename Derived, typename T>
class IGenerator {
public:
    T generate() {
        return static_cast<Derived*>(this)->generate();
    }
};

#endif
