#ifndef STATISTICSLOADER_H
#define STATISTICSLOADER_H

#include <QJsonObject>
#include <QStandardPaths>

class StatisticsLoader
{
public:
    explicit StatisticsLoader();
    ~StatisticsLoader();
    void recordAttempt(const QJsonObject& attempt, const QString& exerciseId);
    QJsonObject load();
private:
    const QString filePath =  QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
                             + "/stats.json";
};

#endif // STATISTICSLOADER_H
