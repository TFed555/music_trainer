#ifndef RECOVERYSTRATEGY_H
#define RECOVERYSTRATEGY_H
#pragma once
#include <functional>
#include "../exceptions/AppException.h"

class RecoveryStrategy {
public:
    using Action = std::function<void()>;
    RecoveryStrategy() = default;
    virtual ~RecoveryStrategy() = default;

    virtual void recover(const AppException& e, Action action) = 0;
};

#endif // RECOVERYSTRATEGY_H
