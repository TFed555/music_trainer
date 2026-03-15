#ifndef CHORDINVERSIONSESSION_H
#define CHORDINVERSIONSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/chords/chordinversioncontroller.h"

class ChordInversionSession : public ISession
{
    Q_OBJECT
public:
    explicit ChordInversionSession(
        NotePlayer* player,
        QObject *parent = nullptr);
    QString title() const override {
        return "Обращение аккорда";
    }
private:
    ChordInversionController* exerciseController;
    ExerciseNoTilesWidget* noTilesView;
};


#endif // CHORDINVERSIONSESSION_H
