#include "statisticssolver.h"
#include <QJsonObject>

StatisticsSolver::StatisticsSolver() {}

QVector<CategoryStats> StatisticsSolver::byCategory(const QMap<QString, QJsonArray>& data) {
    QVector<CategoryStats> res;
    for (auto it = data.begin(); it != data.end(); it++) {
        CategoryStats stats;
        stats.name = it.key();
        stats.total = it.value().size();
        stats.correct = 0;
        for (auto j : it.value()) {
            if (j.toObject()["correct"].toBool()) {
                stats.correct ++;
            }
        }
        res.append(stats);
    }
    return res;
}
