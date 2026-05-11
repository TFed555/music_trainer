#include "logger.h"
#include <QDateTime>
#include <QStandardPaths>
#include <QFile>
#include <QDir>

Logger::Level Logger::currentLevel = Logger::Level::Debug;

void Logger::writeToFile(const QString& log) {
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
                      + "/logs";

    QDir dir(dirPath);
    if (!dir.exists()) dir.mkpath(".");
    QString fileName = QString("%1/app_%2.log")
                           .arg(dirPath)
                           .arg(QDate::currentDate().toString("yyyy-MM-dd"));

    QFile file(fileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream<<log<<"\n";
    }
}

void Logger::log(Level level, const char* src, int line, const char* func, const QString& msg) {
    if (!isEnabled(level)) { return; }
    QString prefix;
    switch(level) {
    case Level::Critical:
        prefix = "[CRITICAL]";
        break;
    case Level::Warning:
        prefix = "[WARNING]";
        break;
    case Level::Debug:
        prefix = "[DEBUG]";
        break;
    case Level::Info:
        prefix = "[INFO]";
        break;
    }
    QString log = QString("%1 %2 %3:%4 (%5) %6")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
            .arg(prefix)
            .arg(src)
            .arg(line)
            .arg(func)
            .arg(msg));

    qDebug().noquote() << log;
    writeToFile(log);
}
