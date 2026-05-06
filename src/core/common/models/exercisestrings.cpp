#include "exercisestrings.h"
#include <QObject>
#include <QMap>
#include <QVector>

const QMap<BlockCategory, ExerciseStrings::BlockConfig> ExerciseStrings::blockConfigs = {
        { BlockCategory::Intervals,
            ExerciseStrings::BlockConfig{
                {
                    ExerciseType::IntervalRecognise,
                    ExerciseType::IntervalIdentify,
                    ExerciseType::IntervalBuild,
                    ExerciseType::IntervalDirection
                }
            }
        },
        { BlockCategory::Chords,
            ExerciseStrings::BlockConfig{
                {
                    ExerciseType::ChordBuild,
                    ExerciseType::ChordIdentify,
                    ExerciseType::ChordInversion,
                    ExerciseType::ChordRoot
                }
            }
        },
        { BlockCategory::Notes,
            ExerciseStrings::BlockConfig{
                {
                    ExerciseType::NoteBuild,
                    ExerciseType::NoteGuess
                }
            }
        },
        { BlockCategory::Rhythm,
            ExerciseStrings::BlockConfig{
                {
                    ExerciseType::RhythmRecognise
                }
            }
        },
        { BlockCategory::Melody,
            ExerciseStrings::BlockConfig{
                {
                    ExerciseType::MelodyDirection,
                    ExerciseType::MelodyRepeat
                }
            }
        }
};

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


QString ExerciseStrings::blockName(BlockCategory category) {
    static const QMap<BlockCategory, const char*> names = {
        {BlockCategory::Intervals, QT_TRANSLATE_NOOP("Blocks", "Интервалы")},
        {BlockCategory::Chords, QT_TRANSLATE_NOOP("Blocks", "Аккорды")},
        {BlockCategory::Notes, QT_TRANSLATE_NOOP("Blocks", "Ноты")},
        {BlockCategory::Rhythm, QT_TRANSLATE_NOOP("Blocks", "Ритм")},
        {BlockCategory::Melody, QT_TRANSLATE_NOOP("Blocks", "Мелодический слух")}
    };
    return QCoreApplication::translate("Blocks", names.value(category, ""));
}
