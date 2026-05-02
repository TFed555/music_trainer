#include "exercisestrings.h"
#include <QObject>

QString ExerciseStrings::displayName(ExerciseType type) {
    switch (type) {
    case ExerciseType::IntervalRecognise:
        return QObject::tr("Определение интервала");
    case ExerciseType::IntervalIdentify:
        return QObject::tr("Название интервала");
    case ExerciseType::IntervalBuild:
        return QObject::tr("Построение интервала");
    case ExerciseType::IntervalDirection:
        return QObject::tr("Направление интервала");
    case ExerciseType::ChordBuild:
        return QObject::tr("Построение аккорда");
    case ExerciseType::ChordIdentify:
        return QObject::tr("Определение типа аккорда");
    case ExerciseType::ChordInversion:
        return QObject::tr("Определение обращения аккорда");
    case ExerciseType::ChordRoot:
        return QObject::tr("Определение основной ноты аккорда");
    case ExerciseType::NoteGuess:
        return QObject::tr("Определение нот в мелодии");
    case ExerciseType::NoteBuild:
        return QObject::tr("Название ноты");
    case ExerciseType::NoteRecognise:
        return QObject::tr("Определение ноты");
    case ExerciseType::RhythmRecognise:
        return QObject::tr("Определение ритма");
    case ExerciseType::MelodyDirection:
        return QObject::tr("Определение направления мелодии");
    case ExerciseType::MelodyRepeat:
        return QObject::tr("Повтор мелодии");
    default:
        return {};
    }
}
