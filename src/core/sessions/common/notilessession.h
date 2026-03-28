#ifndef NOTILESSESSION_H
#define NOTILESSESSION_H

#include "isession.h"
#include "../../controllers/common/ichoiceexercisecontroller.h"
#include "../../gui/exercises/exercisenotileswidget.h"

class NoTilesSession : public ISession
{
    Q_OBJECT
public:
    explicit NoTilesSession(const QString& sessionTitle,
                          QObject* parent = nullptr)
        : ISession(parent), _title(sessionTitle) {

    };

    void setup(IChoiceExerciseController* ctrl, ExerciseNoTilesWidget* w);
    QString title() const override { return _title;}
private:
    QString _title;
};

#endif // NOTILESSESSION_H
