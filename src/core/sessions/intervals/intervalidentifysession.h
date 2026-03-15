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
    QString title() const override {
        return "Определение названия интервала";
    }
private:
    IntervalIdentifyController* exerciseController;
    ExerciseNoTilesWidget* noTilesView;
};

#endif // INTERVALIDENTIFYSESSION_H
