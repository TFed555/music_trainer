#ifndef INTERVALBUILDSESSION_H
#define INTERVALBUILDSESSION_H

#include "isession.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/intervalbuildcontroller.h"

class IntervalBuildSession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalBuildSession(
        QWidget* parentWidget,
        NotePlayer* player,
        QObject* parent = nullptr);
    ExerciseWithTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    ExerciseWithTilesWidget* view;
    IntervalBuildController* exerciseController;
};

#endif // INTERVALBUILDSESSION_H
