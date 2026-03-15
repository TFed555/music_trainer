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
    QString title() const override {
        return "Определение ноты";
    }
private:
    NoteRecogniseController* exerciseController;
    ExerciseWithTilesWidget* tilesView;
};

#endif // NOTERECOGNISESESSION_H
