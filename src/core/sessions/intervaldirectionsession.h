#ifndef INTERVALDIRECTIONSESSION_H
#define INTERVALDIRECTIONSESSION_H

#include "isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/intervaldirectioncontroller.h"

class IntervalDirectionSession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalDirectionSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    ExerciseNoTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    // int noteCounter = 0;
    ExerciseNoTilesWidget* view;
    IntervalDirectionController* exerciseController;
};

#endif // INTERVALDIRECTIONSESSION_H
