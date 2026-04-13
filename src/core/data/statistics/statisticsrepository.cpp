#include "statisticsrepository.h"
#include <QJsonArray>

StatisticsRepository::StatisticsRepository(StatisticsLoader* loader, QObject* parent)
    : loader(loader), QObject(parent) {}

QMap<QString, QJsonArray> StatisticsRepository::loadStatistics() const {
    QJsonObject obj = loader->load();
    QMap<QString, QJsonArray> res;
    QJsonArray values;
    for (const auto& key : obj.keys()) {
        qDebug() << key << "->" << obj[key];
        QJsonValue value = obj.value(key);
        if (value.isArray()) {
            QJsonArray values = value.toArray();
            res[key] = values;
        } else {
            qWarning() << "Expected array for key:" << key;
        }
    }
    return res;
}

void StatisticsRepository::recordStatistics(const Attempt& attempt) {
    QJsonObject obj;

    // obj["exerciseId"] = attempt.exerciseId;
    obj["date"] = attempt.timestamp.toString();
    obj["correctAnswer"] = attempt.correctAnswer;
    obj["userAnswer"] = attempt.userAnswer;
    obj["correct"] = attempt.correct;

    loader->recordAttempt(obj, attempt.exerciseId);
}
