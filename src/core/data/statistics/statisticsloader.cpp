#include "statisticsloader.h"
#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>

StatisticsLoader::StatisticsLoader() {}

StatisticsLoader::~StatisticsLoader() {}

void StatisticsLoader::recordAttempt(const QJsonObject& attempt, const QString& exerciseId) {
    QJsonObject doc = load();

    QJsonArray attempts = doc[exerciseId].toArray();
    if (attempts.isEmpty()) {
        attempts = {};
    }

    attempts.append(attempt);
    doc[exerciseId] = attempts;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(doc).toJson());
        file.close();
    }
}

QJsonObject StatisticsLoader::load() {
    QFile file(filePath);
    QJsonObject doc;
    QDir dir = QFileInfo(filePath).absoluteDir();
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    if (file.open(QIODevice::ReadOnly)) {
        doc = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    }
    return doc;
}
