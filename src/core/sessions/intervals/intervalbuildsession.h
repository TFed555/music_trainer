#ifndef INTERVALBUILDSESSION_H
#define INTERVALBUILDSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/intervals/intervalbuildcontroller.h"

class IntervalBuildSession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalBuildSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    ExerciseWithTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
    QString title() const override {
        return "Построение интервала";
    }
private:
    ExerciseWithTilesWidget* view;
    IntervalBuildController* exerciseController;
};

#endif // INTERVALBUILDSESSION_H
