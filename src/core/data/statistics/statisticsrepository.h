#ifndef STATISTICSREPOSITORY_H
#define STATISTICSREPOSITORY_H

#include "statisticsloader.h"
#include "../../common/models/Attempt.h"

class StatisticsRepository : public QObject
{
    Q_OBJECT
public:
    explicit StatisticsRepository(StatisticsLoader* loader, QObject* parent = nullptr);

    QMap<QString, QJsonArray>  loadStatistics() const;
    void recordStatistics(const Attempt& attempt);
private:
    StatisticsLoader* loader;
};

#endif // STATISTICSREPOSITORY_H
