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
    ExerciseNoTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
    QString title() const override {
        return "Определение направления интервала";
    }
private:
    // int noteCounter = 0;
    ExerciseNoTilesWidget* view;
    IntervalDirectionController* exerciseController;
};

#endif // INTERVALDIRECTIONSESSION_H
