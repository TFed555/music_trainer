#ifndef EXERCISESTRINGS_H
#define EXERCISESTRINGS_H
#include <QString>
#include <QCoreApplication>
#include "ExerciseType.h"

class ExerciseStrings
{
    Q_DECLARE_TR_FUNCTIONS(ExerciseStrings)
public:
    static QString displayName(ExerciseType type);
};

#endif // EXERCISESTRINGS_H
