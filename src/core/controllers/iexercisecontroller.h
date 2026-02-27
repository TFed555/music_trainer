#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"

class IExerciseController : public QObject
{
    Q_OBJECT
public:
    explicit IExerciseController(QObject *parent = nullptr) : QObject(parent) {};

    virtual void start() = 0;
    virtual void stop() = 0;
private:
    NotePlayer* notePlayer;
};

#endif // IEXERCISECONTROLLER_H
