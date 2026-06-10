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
    inline static const QMap<const QString, BlockCategory> jsonToCategory = {
        {"interval", BlockCategory::Intervals},
        {"chord", BlockCategory::Chords},
        {"note", BlockCategory::Notes},
        {"melody", BlockCategory::Melody}
    };
};

#endif // STATISTICSSOLVER_H
