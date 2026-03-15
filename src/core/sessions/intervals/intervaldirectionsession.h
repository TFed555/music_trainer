#ifndef INTERVALDIRECTIONSESSION_H
#define INTERVALDIRECTIONSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/intervals/intervaldirectioncontroller.h"

class IntervalDirectionSession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalDirectionSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    QString title() const override {
        return "Определение направления интервала";
    }
private:
    IntervalDirectionController* exerciseController;
    ExerciseNoTilesWidget* noTilesView;
};

#endif // INTERVALDIRECTIONSESSION_H
