#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include <QString>

class Logger {
public:
    enum class Level { Debug, Info, Warning, Critical };
    static void debug(const QString& msg) {
        log(Level::Debug, msg);
    }
    static void info(const QString& msg) {
        log(Level::Info, msg);
    }
    static void warning(const QString& msg) {
        log(Level::Warning, msg);
    }
    static void critical(const QString& msg) {
        log(Level::Critical, msg);
    }
private:
    static void writeToFile(const QString&);
    static void log(Level, const QString&);
};

#endif // LOGGER_H
