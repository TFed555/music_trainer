#ifndef CHORDINVERSIONSESSION_H
#define CHORDINVERSIONSESSION_H

#include "../common/isession.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../core/controllers/chords/chordinversioncontroller.h"

class ChordInversionSession : public ISession
{
    Q_OBJECT
public:
    explicit ChordInversionSession(
        NotePlayer* player,
        QObject *parent = nullptr);
    ExerciseNoTilesWidget* getWidget() const override {
        qDebug() << "getWidget()" << view; return view;
    }
    QString title() const override {
        return "Обращение аккорда";
    }
private:
    ExerciseNoTilesWidget* view;
    ChordInversionController* exerciseController;
};


#endif // CHORDINVERSIONSESSION_H
