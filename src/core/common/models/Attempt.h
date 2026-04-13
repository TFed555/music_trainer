#ifndef ATTEMPT_H
#define ATTEMPT_H

#include <QString>
#include <QDateTime>

struct Attempt {
    QString exerciseId;
    QString correctAnswer;
    QString userAnswer;
    bool correct;
    QDateTime timestamp;
};

struct RhythmAttempt  {
    QString exerciseId;
    int correct;
    int wrong;
    QDateTime timestamp;
};

#endif // ATTEMPT_H
