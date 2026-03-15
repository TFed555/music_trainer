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
    ExerciseNoTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
    QString title() const override {
        return "Определение нот в мелодии";
    }
private:
    ExerciseNoTilesWidget* view;
    NoteGuessController* exerciseController;
};

#endif // NOTEGUESSSESSION_H
