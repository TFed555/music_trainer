#ifndef CHORDIDENTIFYSESSION_H
#define CHORDIDENTIFYSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/chords/chordidentifycontroller.h"

class ChordIdentifySession : public ISession
{
    Q_OBJECT
public:
    explicit ChordIdentifySession(
        NotePlayer* player,
        QObject *parent = nullptr);
    ExerciseNoTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view;
    }
private:
    ExerciseNoTilesWidget* view;
    ChordIdentifyController* exerciseController;
};

#endif // CHORDIDENTIFYSESSION_H
