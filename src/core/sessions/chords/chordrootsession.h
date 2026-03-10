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
    ExerciseWithTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    int noteCounter = 0;
    ExerciseWithTilesWidget* view;
    ChordRootController* exerciseController;
};

#endif // CHORDROOTSESSION_H
