#ifndef CHORDBUILDSESSION_H
#define CHORDBUILDSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/chords/chordbuildcontroller.h"

class ChordBuildSession : public ISession
{
    Q_OBJECT
public:
    explicit ChordBuildSession(
        NotePlayer* player,
        QObject* parent = nullptr);
    ExerciseWithTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view; }
    QString title() const override {
        return "Построение аккорда";
    }
private:
    ExerciseWithTilesWidget* view;
    ChordBuildController* exerciseController;
};

#endif // CHORDBUILDSESSION_H
