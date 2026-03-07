#ifndef INTERVALIDENTIFYSESSION_H
#define INTERVALIDENTIFYSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/intervals/intervalidentifycontroller.h"

class IntervalIdentifySession : public ISession
{
    Q_OBJECT
public:
    explicit IntervalIdentifySession(
        NotePlayer* player,
        QObject* parent = nullptr);
    ExerciseNoTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
private:
    ExerciseNoTilesWidget* view;
    IntervalIdentifyController* exerciseController;
};

#endif // INTERVALIDENTIFYSESSION_H
