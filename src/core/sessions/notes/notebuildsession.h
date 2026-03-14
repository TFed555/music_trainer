#ifndef NOTEBUILDSESSION_H
#define NOTEBUILDSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/notes/notebuildcontroller.h"

class NoteBuildSession : public ISession
{
    Q_OBJECT
public:
    explicit NoteBuildSession(NotePlayer* player,
                                  QObject* parent = nullptr);
    ExerciseWithTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
    QString title() const override {
        return "Название ноты";
    }
private:
    ExerciseWithTilesWidget* view;
    NoteBuildController* exerciseController;
};

#endif // NOTEBUILDSESSION_H
