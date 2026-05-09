#ifndef GENERATOREXCEPTION_H
#define GENERATOREXCEPTION_H

#include "AppException.h"
#include <QCoreApplication>

class GeneratorException : public AppException {
public:
    explicit GeneratorException(const QString& msg)
        : AppException(userMsg(), msg) {}
private:
    static QString userMsg() {
        return QCoreApplication::translate("GeneratorException",
                                           "Не удалось создать упражнение, повторите попытку");
    }
};

#endif // GENERATOREXCEPTION_H
