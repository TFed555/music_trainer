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
    QString title() const override {
        return "Название ноты";
    }
private:
    NoteBuildController* exerciseController;
    ExerciseWithTilesWidget* tilesView;
};

#endif // NOTEBUILDSESSION_H
