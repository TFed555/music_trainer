#ifndef NOTERECOGNISESESSION_H
#define NOTERECOGNISESESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/notes/noterecognisecontroller.h"

class NoteRecogniseSession : public ISession
{
    Q_OBJECT
public:
    explicit NoteRecogniseSession(NotePlayer* player,
                         QObject* parent = nullptr);
    ExerciseWithTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
    QString title() const override {
        return "Определение ноты";
    }
private:
    ExerciseWithTilesWidget* view;
    NoteRecogniseController* exerciseController;
};

#endif // NOTERECOGNISESESSION_H
