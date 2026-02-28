#ifndef INTERVALRECOGNISESESSION_H
#define INTERVALRECOGNISESESSION_H

#include "isession.h"
#include "../../gui/exercises/intervalexercisewidget.h"
#include "../core/controllers/intervalrecognisecontroller.h"

class IntervalRecogniseSession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalRecogniseSession(
        QWidget* parentWidget,
        NotePlayer* player,
        QObject* parent = nullptr);
    IntervalExerciseWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    int noteCounter = 0;
    IntervalExerciseWidget* view;
    IntervalRecogniseController* exerciseController;
};

#endif // INTERVALRECOGNISESESSION_H
