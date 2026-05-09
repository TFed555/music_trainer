#ifndef IGENERATOR_H
#define IGENERATOR_H
#pragma once
#include "../core/common/exceptions/GeneratorException.h"
#include "../core/common/recovery/RetryStrategy.h"

template <typename Derived, typename T>
class IGenerator {
public:
    T generate() {
        T res;
        strategy->recover(GeneratorException("Generator failed"),
                          [&] () {
                              res = static_cast<Derived*>(this)->doGenerate();
        });
        return res;
    }
protected:
    virtual T doGenerate() = 0;
private:
    std::unique_ptr<RetryStrategy> strategy
        = std::make_unique<RetryStrategy>(100);
};

#endif
