#ifndef INTERVALIDENTIFYSESSION_H
#define INTERVALIDENTIFYSESSION_H

#include "isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/intervalidentifycontroller.h"

class IntervalIdentifySession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalIdentifySession(
        // QWidget* parentWidget,
        NotePlayer* player,
        QObject* parent = nullptr);
    ExerciseNoTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    int noteCounter = 0;
    ExerciseNoTilesWidget* view;
    IntervalIdentifyController* exerciseController;
};

#endif // INTERVALIDENTIFYSESSION_H
