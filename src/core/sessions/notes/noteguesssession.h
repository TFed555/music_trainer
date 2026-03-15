#ifndef NOTEGUESSSESSION_H
#define NOTEGUESSSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/notes/noteguesscontroller.h"

class NoteGuessSession : public ISession
{
    Q_OBJECT
public:
    explicit NoteGuessSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    QString title() const override {
        return "Определение нот в мелодии";
    }
private:
    NoteGuessController* exerciseController;
    ExerciseNoTilesWidget* noTilesView;
};

#endif // NOTEGUESSSESSION_H
