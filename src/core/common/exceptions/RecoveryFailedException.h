#ifndef RECOVERYFAILEDEXCEPTION_H
#define RECOVERYFAILEDEXCEPTION_H

#include "AppException.h"

class RecoveryFailedException : public AppException {
public:
    explicit RecoveryFailedException(const AppException& e)
        : AppException(e.userMsg, QString("Recovery failed")) {}
};


#endif // RECOVERYFAILEDEXCEPTION_H
