#ifndef RHYTHMRECOGNISESESSION_H
#define RHYTHMRECOGNISESESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exerciserhythmwidget.h"
#include "../core/controllers/rhythm/rhythmrecognisecontroller.h"

class RhythmRecogniseSession : public ISession
{
    Q_OBJECT
public:
    explicit RhythmRecogniseSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    QString title() const override {
        return "Определение ритма";
    }
private:
    RhythmRecogniseController* exerciseController;
    ExerciseRhythmWidget* rhythmView;
};

#endif // RHYTHMRECOGNISESESSION_H
