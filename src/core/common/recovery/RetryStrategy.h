#ifndef RETRYSTRATEGY_H
#define RETRYSTRATEGY_H
#pragma once

#include "RecoveryStrategy.h"
#include "../exceptions/RecoveryFailedException.h"

class RetryStrategy : RecoveryStrategy {
public:
    explicit RetryStrategy(int maxAttempts) : maxAttempts(maxAttempts){};

    void recover(const AppException& e, Action action) override {
        for (int i = 0; i < maxAttempts; i++) {
            try {
                action();
                return;
            } catch(const AppException& e) {
                if (i+1 == maxAttempts) {
                    throw RecoveryFailedException(e);
                }
            }
        }
    }
private:
    int maxAttempts;
};


#endif // RETRYSTRATEGY_H
