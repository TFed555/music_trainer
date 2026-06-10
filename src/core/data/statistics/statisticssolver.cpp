#include "statisticssolver.h"
#include <QJsonObject>

StatisticsSolver::StatisticsSolver() {}

QVector<CategoryStats> StatisticsSolver::byCategory(const QMap<QString, QJsonArray>& data) {
    QMap<BlockCategory, CategoryStats> grouped;

    for (auto it = data.begin(); it != data.end(); it++) {
        BlockCategory cat = jsonToCategory[it.key().split(".")[0]];

        auto& stats = grouped[cat];
        stats.category = cat;
        stats.total += it.value().size();

        for (auto j : it.value()) {
            if (j.toObject()["correct"].toBool()) {
                stats.correct++;
            }
        }
    }

    return grouped.values().toVector();
}
