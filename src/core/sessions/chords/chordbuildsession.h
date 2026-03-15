#ifndef CHORDBUILDSESSION_H
#define CHORDBUILDSESSION_H

#include "../common/isession.h"
#include "../core/controllers/chords/chordbuildcontroller.h"
#include "../../gui/exercises/exercisewithtileswidget.h"

class ChordBuildSession : public ISession
{
    Q_OBJECT
public:
    explicit ChordBuildSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    QString title() const override {
        return "Построение аккорда";
    }
private:
    ChordBuildController* exerciseController;
    ExerciseWithTilesWidget* tilesView;
};

#endif // CHORDBUILDSESSION_H
