#ifndef CHORDROOTSESSION_H
#define CHORDROOTSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/chords/chordrootcontroller.h"


class ChordRootSession : public ISession
{
    Q_OBJECT
public:
    explicit ChordRootSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    QString title() const override {
        return "Определение основной ноты аккорда";
    }
private:
    int noteCounter = 0;
    ChordRootController* exerciseController;
    ExerciseWithTilesWidget* tilesView;
};

#endif // CHORDROOTSESSION_H
