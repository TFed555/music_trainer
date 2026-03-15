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
    QString title() const override {
        return "Построение интервала";
    }
private:
    IntervalBuildController* exerciseController;
    ExerciseWithTilesWidget* tilesView;
};

#endif // INTERVALBUILDSESSION_H
