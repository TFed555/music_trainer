#ifndef STATISTICSSOLVER_H
#define STATISTICSSOLVER_H

#include <QObject>
#include "../../common/models/StatisticsModel.h"
#include "QJsonArray"

class StatisticsSolver
{
public:
    StatisticsSolver();
    QVector<CategoryStats> byCategory(const QMap<QString, QJsonArray>&);
};

#endif // STATISTICSSOLVER_H
