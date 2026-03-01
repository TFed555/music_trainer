#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"

class IExerciseController : public QObject
{
    Q_OBJECT
public:
    explicit IExerciseController(QObject *parent = nullptr) : QObject(parent) {};

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
signals:
    void inputFinished();

private:
    QVector<QString> correctAnswer;
    QVector<QString>  userAnswer;
    NotePlayer* notePlayer;
};

#endif // IEXERCISECONTROLLER_H
