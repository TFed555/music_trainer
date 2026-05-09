#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <stdexcept>
#include <QString>

class AppException : public std::logic_error {
public:
    explicit AppException(const QString& userMsg, const QString& msg)
        : std::logic_error(msg.toStdString())
        , userMsg(userMsg){}
    QString userMsg;
};

#endif // APPEXCEPTION_H
