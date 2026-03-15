#ifndef INTERVALRECOGNISESESSION_H
#define INTERVALRECOGNISESESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/intervals/intervalrecognisecontroller.h"

class IntervalRecogniseSession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalRecogniseSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    QString title() const override {
        return "Определение интервала";
    }
private:
    IntervalRecogniseController* exerciseController;
    ExerciseWithTilesWidget* tilesView;
};

#endif // INTERVALRECOGNISESESSION_H
