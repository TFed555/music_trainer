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
        // QWidget* parentWidget,
        NotePlayer* player,
        QObject* parent = nullptr);

    ExerciseWithTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    int noteCounter = 0;
    ExerciseWithTilesWidget* view;
    IntervalRecogniseController* exerciseController;
};

#endif // INTERVALRECOGNISESESSION_H
