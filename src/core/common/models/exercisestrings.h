#ifndef EXERCISESTRINGS_H
#define EXERCISESTRINGS_H
#include <QString>
#include <QCoreApplication>
#include "ExerciseType.h"
#include "BlockCategory.h"

class ExerciseStrings
{
    Q_DECLARE_TR_FUNCTIONS(ExerciseStrings)
public:
    struct BlockConfig {
        QVector<ExerciseType> exercises;
    };

    static const QMap<BlockCategory, BlockConfig> blockConfigs;
    static QString displayName(ExerciseType type);
    static QString blockName(BlockCategory category);
};

#endif // EXERCISESTRINGS_H
