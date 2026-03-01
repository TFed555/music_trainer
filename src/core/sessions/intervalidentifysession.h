#ifndef INTERVALIDENTIFYSESSION_H
#define INTERVALIDENTIFYSESSION_H

#include "isession.h"
#include "../../gui/exercises/intervalexercisewidget.h"
#include "../core/controllers/intervalidentifycontroller.h"
#include <QObject>

class IntervalIdentifySession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalIdentifySession(
        QWidget* parentWidget,
        NotePlayer* player,
        QObject* parent = nullptr);
    IntervalExerciseWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    int noteCounter = 0;
    IntervalExerciseWidget* view;
    IntervalIdentifyController* exerciseController;
};

#endif // INTERVALIDENTIFYSESSION_H
