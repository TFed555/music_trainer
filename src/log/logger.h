#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include <QString>

#define LOG_DEBUG(msg)    Logger::log(Logger::Level::Debug, __FILE__, __LINE__, __FUNCTION__, msg)
#define LOG_INFO(msg)     Logger::log(Logger::Level::Info, __FILE__, __LINE__, __FUNCTION__, msg)
#define LOG_WARNING(msg)  Logger::log(Logger::Level::Warning, __FILE__, __LINE__, __FUNCTION__, msg)
#define LOG_CRITICAL(msg) Logger::log(Logger::Level::Critical, __FILE__, __LINE__, __FUNCTION__, msg)

class Logger {
public:
    enum class Level { Debug, Info, Warning, Critical };
    static void log(Level level, const char* src, int line, const char* func, const QString& msg);
    static void setLevel(Level lvl) { currentLevel = lvl; }
private:
    static bool isEnabled(Level lvl) {
        return lvl >= currentLevel;
    }
    static void writeToFile(const QString&);
    static Level currentLevel;
};

#endif // LOGGER_H
