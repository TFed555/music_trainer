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
    QString title() const override {
        return "Определение аккорда";
    }
private:
    ChordIdentifyController* exerciseController;
    ExerciseNoTilesWidget* noTilesView;
};

#endif // CHORDIDENTIFYSESSION_H
